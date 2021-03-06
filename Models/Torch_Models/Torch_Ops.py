#!/usr/bin/env python
# coding: utf-8
"""
module: some self-constructed torch ops, mostly functional
"""

import torch.nn as nn
import torch.nn.functional as F


""" padding """

def average_padding(input, padding):
    """
    only tested for 2D padding
    Args:
        inputs: Assumed in NCHW format
        padding: A tuple-like value to specify padding at one side
    """
    pad_val = input.mean(dim = (-1, -2))
    out_dims = input.size()
    out_dims = out_dims[:-2] + (out_dims[-2] + padding[-2] * 2, out_dims[-1] + padding[-1] * 2)  # expand HW only
    out_tensor = pad_val.unsqueeze(-1).unsqueeze(-1).repeat(1, 1, *out_dims[-2:])  # filled with desired value
    # copy original val
    out_tensor[...,
               padding[0]: out_dims[-2] - padding[0],
               padding[1]: out_dims[-1] - padding[1]] = input
    return out_tensor


""" cross-correlation """


def xcorr_fast(x, kernel):
    """
    group conv2d to calculate cross correlation, fast version
    """
    batch = kernel.size()[0]
    pk = kernel.view(-1, x.size()[1], kernel.size()[2], kernel.size()[3])
    px = x.view(1, -1, x.size()[2], x.size()[3])
    po = F.conv2d(px, pk, groups=batch)
    po = po.view(batch, -1, po.size()[2], po.size()[3])
    return po


def xcorr_depthwise(x, kernel):
    """
    depthwise (channel-wise) cross correlation
    """
    batch = kernel.size(0)
    channel = kernel.size(1)
    x = x.view(1, batch*channel, x.size(2), x.size(3))
    kernel = kernel.view(batch*channel, 1, kernel.size(2), kernel.size(3))
    out = F.conv2d(x, kernel, groups=batch*channel)
    out = out.view(batch, channel, out.size(2), out.size(3))
    return out


""" loss """


def cls_loss(pred, label, select):
    if len(select.size()) == 0:
        return 0
    pred = torch.index_select(pred, 0, select)
    label = torch.index_select(label, 0, select)
    return F.nll_loss(pred, label)


def select_cross_entropy_loss(pred, label):
    pred = pred.view(-1, 2)
    label = label.view(-1)
    pos = label.data.eq(1).nonzero().squeeze().cuda()  # use only 0-1 label
    neg = label.data.eq(0).nonzero().squeeze().cuda()
    loss_pos = cls_loss(pred, label, pos)
    loss_neg = cls_loss(pred, label, neg)
    return loss_pos * 0.5 + loss_neg * 0.5


def weight_l1_loss(pred_loc, label_loc, loss_weight):
    b, _, sh, sw = pred_loc.size()
    pred_loc = pred_loc.view(b, 4, -1, sh, sw)
    diff = (pred_loc - label_loc).abs()
    diff = diff.sum(dim=1).view(b, -1, sh, sw)
    loss = diff * loss_weight
    return loss.sum().div(b)


""" save & restore """


def check_keys(model, state_dict):
    """
    check coverage between loaded var (state_dict) & model var (model.state_dict())
    """
    ckpt_keys = set(state_dict.keys())
    model_keys = set(model.state_dict().keys())

    used_pretrained_keys = model_keys & ckpt_keys
    unused_pretrained_keys = ckpt_keys - model_keys
    missing_keys = model_keys - ckpt_keys
    missing_keys = [x for x in missing_keys if not x.endswith('num_batches_tracked')]  # filter 'num_batches_tracked'

    if len(missing_keys) > 0:
        print('[Warning] missing_keys, num=', len(missing_keys), ':\n', missing_keys)        
    if len(unused_pretrained_keys) > 0:
        print('[Warning] unused_pretrained_keys, num=', len(unused_pretrained_keys), ':\n', unused_pretrained_keys)
    print('used keys', len(used_pretrained_keys))
    return len(used_pretrained_keys) > 0

def restore(model, save_file, optimizer=None, device='cpu'):
    if device == 'cpu':
        ckpt_dict = torch.load(save_file, map_location=lambda storage, loc: storage.cpu())
    else:  # load into gpu
        device = torch.cuda.current_device()
        ckpt_dict = torch.load(save_file, map_location=lambda storage, loc: storage.cuda(device))

    # load model
    state_dict = ckpt_dict['state_dict'] if "state_dict" in state_dict.keys() else ckpt_dict
    
    pfx = 'module.'  # remove prefix 'module.' (old style saved model)
    state_dict = {k[len(pfx):] if k.startswith(pfx) else k: v for k, v in state_dict.items()}

    if not check_keys(model, state_dict):  # check keys in loaded state_dict
        print('retry after adding prefix \'features.\'')  # retry
        state_dict = {'features.' + k: v for k, v in state_dict}
        if not check_keys(model, state_dict):
            raise AttributeError('nothing loaded from save_file= ' + save_file)
    model.load_state_dict(state_dict, strict=False)

    # load optimizer
    if 'optimizer' in ckpt_dict and optimizer is not None:
        if check_keys(optimizer, ckpt['optimizer']):
            optimizer.load_state_dict(ckpt['optimizer'])
    
    epoch = ckpt['epoch'] if 'epoch' in ckpt else 0

    return model, optimizer, epoch


""" parallel & distributed compute """


def data_parallel(module, input, device_ids, output_device=None):
    if not device_ids:
        return module(input)

    if output_device is None:
        output_device = device_ids[0]

    replicas = nn.parallel.replicate(module, device_ids)  # replicate across devices
    inputs = nn.parallel.scatter(input, device_ids)  # split the input across first-dim (batch)
    replicas = replicas[:len(inputs)]  # guard against batch_size < gpu_num
    outputs = nn.parallel.parallel_apply(replicas, inputs)  # start parallel compute
    return nn.parallel.gather(outputs, output_device)  # gather the output (concat back into together in first-dim)

def ring_allreduce(send, recv):
    """ 
    a ring-allreduce with addition:
        send: local tensor to send
        recv: local buffer to receive
    could use torch.chunk to further utilize communication bandwidth (divide tensor into chunks)
    """
    rank = dist.get_rank()
    size = dist.get_world_size()
    send_buff = torch.zeros(send.size())
    recv_buff = torch.zeros(send.size())
    accum = torch.zeros(send.size())
    accum[:] = send[:]

    # determine the neighbore to: recv from left & send to right
    left = ((rank - 1) + size) % size
    right = (rank + 1) % size

    for i in range(size - 1): # need to send & recv for N-1 times (N = world size = usually, gpu num)
        if i % 2 == 0:
            # Send send_buff
            send_req = dist.isend(send_buff, right)
            dist.recv(recv_buff, left)
            accum[:] += recv[:]
        else:
            # Send recv_buff
            send_req = dist.isend(recv_buff, right)
            dist.recv(send_buff, left)
            accum[:] += send[:]
        send_req.wait() # wait till send() finish (isend to postpone blocking)
    recv[:] = accum[:]