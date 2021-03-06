#!/usr/bin/env python
# coding: utf-8
"""
module: base class for feeding data
"""

import os
import re
import sys
import pathlib  # 
import numpy as np


class File_Traverser(object):
    """
    traverse file given root dir with an optional fileter
    """
    def __init__(self, data_dir, re_expr='.*'):
        self.data_dir = data_dir
        self.re_expr = re_expr

        if type(data_dir) is list:
            path_list = []
            for d in data_dir:
                path_list.extend([(dir_p, fname) for dir_p, _, files in os.walk(os.path.expanduser(d)) for fname in files if self._chk_re_expr(fname)])
        else:
            assert type(data_dir) is str
            path_list = [(dir_p, fname) for dir_p, _, files in os.walk(os.path.expanduser(data_dir)) for fname in files if self._chk_re_expr(fname)]
        
        self.path_list = path_list

    def _chk_re_expr(self, string):
        return bool(re.fullmatch(self.re_expr, string))
    
    def traverse_file(self):
        """
        yield dir path and file name
        """
        for dirpath, fname in self.path_list:
            yield(dirpath, fname)

    def traverse_file_path(self):
        """
        yield joined path
        """
        for dirpath, fname in self.path_list:
            yield os.path.join(dirpath, fname)

    def list_all_file_path(self, sort=True):
        """
        get all paths to selected files in list
        """
        path_list = self.path_list.copy()
        if sort:
            path_list = sorted(path_list)
        return path_list

class Gen_Feeder(object):
    """
    base class to feed from a (list of) data dir(s)
    """
    def __init__(self, data_dir, class_num, class_name=None, re_expr='.*', use_onehot=True, split=None, weight_type='', norm_type=''):
        self.data_dir = data_dir
        self.traverser = File_Traverser(data_dir, re_expr=re_expr)

        self.class_num = class_num
        if class_name is None:
            class_name = dict(zip(range(class_num), [str(n) for n in range(class_num)]))
        elif not (type(class_name) is dict):  # treat as iterable
            class_name = dict(zip(range(class_num), class_name))
        self.class_name = class_name

        self.use_onehot = use_onehot
        self.split = split
        self.weight_type = weight_type
        self.norm_type = norm_type
        self.ext_module = dict()

        if split is not None:
            split = [int(i) for i in split.split('-')]
            np.random.shuffle(self.traverser.path_list)

            split_unit = len(self.traverser.path_list) / sum(split)
            split_point = [0]
            split_point.extend([int(i) for i in split_unit * np.cumsum(split)[:-1]])
            
            self.path_split = []
            for i in range(len(split_point) - 1):
                start_i = split_point[i]
                end_i = split_point[i + 1]
                self.path_split.append(self.traverser.path_list[start_i:end_i])
            self.path_split.append(self.traverser.path_list[end_i:])
            self.switch_split(0)

    def switch_split(self, split_n, shuffle=False):
        """
        switch the split of the path list to use
        """
        if shuffle:
            self.shuffle(split_n)
        self.traverser.path_list = self.path_split[split_n]

    def shuffle(self, split_n=-1):
        if split_n == -1:  # shuffle all
            for i in range(len(self.path_split)):
                np.random.shuffle(self.path_split[i])
        else:
            np.random.shuffle(self.path_split[split_n])

    def _cal_weight(self):
        """
        calculate weight
        """
        def _cal_bal(): # calculate weight from current dataset
            cnt_arr = np.zeros(self.class_num)
            for _, cur_label in self.iterate_data():
                cnt_arr += cur_label.reshape(-1, self.class_num).sum(axis=0)
            
            weight_arr = np.array([cnt_arr.sum() - cnt_arr[idx] for idx in range(self.class_num)])
            return weight_arr / weight_arr.sum() / (self.class_num - 1)
        def _cal_w():
            if self.weight_type == 'bal':
                weights = _cal_bal()
            else:
                weights = list()
            return weights

        if self.split is not None:
            self.weight = []
            for split_n in range(len(self.path_split)): # for each data split
                self.switch_split(split_n)
                self.weight.append(_cal_w())
            self.switch_split(0)
        else:
            self.weight = _cal_w()

    def _cal_norm(self):
        raise NotImplementedError

    def _to_onehot(self, label_list):
        """
        transform **a 1-D list** of label into one-hot label
        """
        height = len(label_list)
        
        label = np.zeros((height, self.class_num), dtype=int)
        label[np.arange(height), label_list] = 1

        return label

    def _get_input_label_pair(self, dirpath, name):
        raise NotImplementedError

    def iterate_data(self):
        """
        iterate through the dataset for once
        feed one example a time
        """
        for dirpath, name in self.traverser.traverse_file():
            yield from self._get_input_label_pair(dirpath, name)

    def get_all_data(self):
        """
        dangerous: feed all data at once
        use unless small enough & cannot partial fit
        """
        input_list = []
        label_list = []
        for cur_input, cur_label in self.iterate_data():
            input_list.append(cur_input)
            label_list.append(cur_label)

        return input_list, label_list

    def _record_pred(self, data_dirpath, data_name, pred_func, model_name, out_subdir, overwrite):
        raise NotImplementedError
    
    def record_prediction(self, pred_func, model_name, output_dir='./Prediction', dataset_name='Data', overwrite=False, options=dict()):
        """
        record the prediction with the same dir struct as data
        must be provided a func to predict data in one file
        """
        #TODO: may transfer to a hd5f each dataset to obviate various dataset struct & to have consistent prediction struct
        for dirpath, name in self.traverser.traverse_file():
            # create corresponding dir struct
            dir_list = dirpath.strip('/').split('/')
            subdir = '/'.join(dir_list[dir_list.index(dataset_name) + 1:])
            out_subdir = os.path.join(output_dir, subdir)
            os.makedirs(out_subdir, exist_ok=True)

            # pred & write into file
            self._record_pred(dirpath, name, pred_func, model_name, out_subdir, overwrite)

    def iterate_with_metadata(self, data_dir, data_name):
        """
        iterate over data with corresponding meta data
        """
        raise NotImplementedError

class Gen_CVFeeder(Gen_Feeder):
    """
    feed data in a cross-validation fashion
    TODO: finish building the class: to cooperate with cross validation
    """
    def __init__(self, data_dir, class_num, fold_num, re_expr='.*', use_onehot=True):
        super(Gen_CVFeeder, self).__init__(data_dir, class_num, re_expr=re_expr, use_onehot=use_onehot, split=[1] * fold_num)
        raise NotImplementedError

class Feeder(object):
    """
    base class to feed data based on a file to map: key -> input-label pair
    """
    def __init__(self, data_ref_path, class_num, class_name=None, use_onehot=True, config={}):
        self.data_ref_path = data_ref_path
        self.data_ref = None

        self.class_num = class_num
        if class_name is None:
            class_name = dict(zip(range(class_num), [str(n) for n in range(class_num)]))
        elif not (type(class_name) is dict):  # treat as iterable
            class_name = dict(zip(range(class_num), class_name))
        self.class_name = class_name

        self.use_onehot = use_onehot
        self.config = config
        self.ext_module = dict()

    def _to_onehot(self, label_list):
        """
        transform **a 1-D list** of label into one-hot label
        """
        height = len(label_list)
        
        label = np.zeros((height, self.class_num), dtype=int)
        label[np.arange(height), label_list] = 1

        return label
    
    def _load_data_ref(self):
        return None

    def _get_input_label_pair(self, ref):
        raise NotImplementedError

    def iterate_data(self):
        """
        iterate through the dataset for once; one example a time
        """
        for ref in self.data_ref:
            yield self._get_input_label_pair(ref)

    def iterate_forever(self, batch_size=None):
        """
        iterate data/batch as infinite generator
        """
        data_gen = self.iterate_data()
        while True:
            try:
                yield next(data_gen)
            except StopIteration:
                self.reset()
                data_gen = self.iterate_data()
                pass

    def reset(self):
        """
        reset & randomize the feeder
        """
        np.random.shuffle(self.data_ref)

    def iterate_with_metadata(self):
        """
        iterate over data with corresponding meta data
        """
        raise NotImplementedError

class Parallel_Feeder(object):
    """
    construct a parallel py-process to load data: enable loading-training pipeline
    warning: should NOT modify passed in feeder afterwards
    """
    def __init__(self, feeder, buffer_size=5, worker_num=1, verbose=False):
        super(Parallel_Feeder, self).__init__()

        assert isinstance(feeder, Feeder)  # a data feeder with mapping: key -> input-label
        self.__feeder = feeder
        self.__data_ref = feeder.data_ref  # mapping to load each input-label pair

        self.__config = {'alive': True,
                         'buffer_size': buffer_size,
                         'worker_num': worker_num,
                         'wrapable': False}
        self.verbose = verbose

        self.mp = __import__('multiprocessing', fromlist=[''])
        self.__worker = []
        self.__buffer = None
        self.__config_lock = None

    def _create_worker(self):
        # distribute data_keys to each worker
        ref_segment = int(np.ceil(len(self.__data_ref) / self.__config['worker_num']))
        for cnt in range(self.__config['worker_num']):
            start = cnt * ref_segment
            end = start + ref_segment
            if self.verbose:
                print('creating worker with allocated data num = ', len(self.__data_ref[start:end]))
            self.__worker.append(self.mp.Process(target=self.__fill_buffur, args=(self.__data_ref[start:end],)))
        # start running
        for w in self.__worker:
            w.start()

    def shutdown(self):
        """
        stop workers & clean up
        """
        for p in self.__worker:
            p.terminate()
        for p in self.__worker:
            p.join()

        self.__worker = []
        if self.__buffer is not None:
            self.__buffer.close()
        self.__config_lock = None
            
    def refresh(self, feeder=None, config=None):
        """
        clean up & prepare for new workers
        """
        self.shutdown()
        if config:
            for k in config:
                self.__config[k] = config[k]
        if feeder:
            self.__feeder = feeder
            self.__data_ref = feeder.data_ref
        # new lock, new queue
        self.__config_lock = self.mp.Lock()  # lock for state reading/setting
        self.__buffer = self.mp.Queue(maxsize=self.__config['buffer_size'])  # buffer for filling data
    
    def __del__(self):
        self.shutdown()

    def __read_config(self):
        # atomic read current config
        self.__config_lock.acquire()
        config = self.__config.copy()  # copy dict
        self.__config_lock.release()
        return config

    def set_config(self, config):
        """
        change the config on-the-fly
        """
        self.__config_lock.acquire()
        for k in config:
            self.__config[k] = config[k]
        self.__config_lock.release()

    def __fill_buffur(self, data_ref):
        # running in parallel: use pure (stateless) function only
        data_generator = (self.__feeder._get_input_label_pair(r) for r in data_ref)
        # random.choices(data_keys, weights=[...]) for random sample
        while True:
            config = self.__read_config()
            try:
                cur_input, cur_label = next(data_generator)
            except StopIteration:
                # renew generator
                np.random.shuffle(data_ref)
                data_generator = (self.__feeder._get_input_label_pair(r) for r in data_ref)
                
                if config['wrapable']: # if wrap around
                    cur_input, cur_label = next(data_generator)
                    pass
                else:  # not to wrap: stop here
                    config['alive'] = False
                    break
            self.__buffer.put((cur_input, cur_label))
            
            if not config['alive']:
                break

    def iterate_data(self, timeout=10):
        """
        entry for main process: iterate through dataset for once; one batch a time
        """
        self.__config['wrapable'] = False
        self.refresh()
        self._create_worker() # workers start runnning
        cnt = 0
        while True:
            cnt += 1
            try:
                data = self.__buffer.get(timeout=timeout)  # potentially blocking
            except:
                print('------------>')
                print('timeout when trying to read the %dth data' % cnt)
                if self.verbose:
                    print('current data:\n', data)
                print('<------------')
                break
            yield data
            if cnt >= len(self.__data_ref):  # finished
                break

    def iterate_forever(self, timeout=10):
        """
        entry for main process: create running-forever workers and a handle func to get data
        """
        self.__config['wrapable'] = True
        self.refresh()
        self._create_worker()
        while True:
            try:
                data = self.__buffer.get(timeout=timeout)  # potentially blocking
            except:
                print('------------>')
                print('timeout when trying to read')
                print('<------------')
                raise
            yield data
