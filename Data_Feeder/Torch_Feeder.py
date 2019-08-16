#!/usr/bin/env python
# coding: utf-8
'''
module: pipeline to solve data-related problem for neural net built by py-torch (using torch.utils.data.Dataset)
    note: torch conv default input: [N, C, H, W], N=batch size, C=channel, H/W = high/width
'''

import torch
import numpy as np

from torch.utils.data import Dataset
from . import Data_Feeder as feeder

class Imagenet_VID_Feeder(Dataset):
    '''
    wrapper from feeder to torch data.Dataset
    '''

    def __init__(self, data_ref_path):
        super(Imagenet_VID_Feeder, self).__init__()
        self.feeder = feeder.Imagenet_VID_Feeder(data_ref_path, 30)
        
        