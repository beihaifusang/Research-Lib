#!/usr/bin/env python
# coding: utf-8
'''
module: base class for feeding data
'''

import os
import re
import sys
import numpy as np
import tensorflow as tf

class File_Traverser(object):
    '''
    traverse file given root dir with an optional fileter
    '''
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
        '''
        yield dir path and file name
        '''
        for dirpath, fname in self.path_list:
            yield(dirpath, fname)

    def traverse_file_path(self):
        '''
        yield joined path
        '''
        for dirpath, fname in self.path_list:
            yield os.path.join(dirpath, fname)

    def list_all_file_path(self, sort=True):
        '''
        get all paths to selected files in list
        '''
        path_list = self.path_list.copy()
        if sort:
            path_list = sorted(path_list)
        return path_list


class TF_Feeder(object):
    '''
    base class to build a tf.data pipeline
    '''
    def __init__(self, data_path):
        self.data_path = data_path
    
    def _get_dataset(self):
        raise NotImplementedError

    def config_dataset(self, epoch=1, batch=1, shuffle=True, shuffle_buf=100):
        '''
        get a configured dataset
        '''
        dataset = self._get_dataset()
        dataset = dataset.repeat(epoch)
        dataset = dataset.batch(batch)
        if shuffle:
            dataset = dataset.shuffle(buffer_size=shuffle_buf)
        return dataset

    def get_general_iterator(self, epoch=1, batch=1, shuffle=True, shuffle_buf=100):
        '''
        get general iterator => enable to switch dataset 
        '''
        dataset = self.config_dataset(epoch=epoch, batch=batch, shuffle=shuffle, shuffle_buf=shuffle_buf)
        return tf.data.Iterator.from_structure(dataset.output_types, dataset.output_shapes)
    
    def get_dataset_iterator(self, epoch=1, batch=1, shuffle=True, shuffle_buf=100, one_shot=False):
        '''
        construct tf.train.Dataset iterators to feed batches
        to use, see https://www.tensorflow.org/guide/datasets
        '''
        dataset = self.config_dataset(epoch=epoch, batch=batch, shuffle=shuffle, shuffle_buf=shuffle_buf)

        if one_shot:
            iterator = dataset.make_one_shot_iterator()            
        else:
            iterator = dataset.make_initializable_iterator()

        return iterator


class TFRecord_Feeder(TF_Feeder):
    '''
    base class to build a tf.data pipeline from a .tfrecord
    '''
    def __init__(self, data_path, features_dict):
        super(TFRecord_Feeder, self).__init__(data_path)
        self.features_dict = features_dict

    # decode an example in the form of bytes
    def _decode_byte(self, example):
        raise NotImplementedError

    def feed(self):
        '''
        to get next example from the tfrecord
        '''
        self.record_iterator = tf.python_io.tf_record_iterator(path=self.data_path)
        for raw_example in self.record_iterator:
            example = tf.train.Example()
            example.ParseFromString(raw_example)

            yield self._decode_byte(example)

    # decode the tensor resulted from reading tfrecord - mainly by tf.decode_raw(bytes, out_type)
    def _decode_to_tensor(self, serialized_example):
        raise NotImplementedError

    def construct_batch_feeder(self, batch_size, shuffle=True, capacity=None, min_after_dequeue=None, num_threads=1):
        '''
        Deprecate! - replaced by tf.train.Dataset
        construct tensor(s) to feed batches, to start a feeder: 
            coord = tf.train.Coordinator()
            threads = tf.train.start_queue_runners(coord=coord)
        '''
        if not capacity:
            capacity = 10 * batch_size
        if not min_after_dequeue: # minimal number after dequeue - for the level of mixing
            min_after_dequeue = batch_size

        # generate a queue to read => only single file supported now
        filename_queue = tf.train.string_input_producer([self.data_path])

        reader = tf.TFRecordReader()
        _, serialized_example = reader.read(filename_queue)   # get file name & file
        input_label_tensor_pair = self._decode_to_tensor(serialized_example)

        if shuffle:
            batch_feeder = tf.train.shuffle_batch(input_label_tensor_pair, batch_size=batch_size, capacity=capacity, num_threads=num_threads, min_after_dequeue=min_after_dequeue, allow_smaller_final_batch=True)
        else:
            batch_feeder = tf.train.batch(input_label_tensor_pair, batch_size=batch_size, capacity=capacity, num_threads=num_threads, allow_smaller_final_batch=True)
        
        return batch_feeder # a list of tensors for corresponding input

    def _get_dataset(self):
        dataset =  tf.contrib.data.TFRecordDataset(self.data_path)
        dataset = dataset.map(self._decode_to_tensor)  # Parse the example protobuf into tensors
        return dataset


class TF_CSV_Feeder(TF_Feeder):
    '''
    base class to construct tf.data pipeline to read, parse & feed CSV data
    TODO: implement deprecate pipeline threading for backward compatibility
    '''
    def __init__(self, data_path, record_defaults, select_cols=None, header=True, recursive=True, re_expr='.*'):
        super(TF_CSV_Feeder, self).__init__(data_path)
        self.record_defaults = record_defaults
        self.select_cols = select_cols
        self.header = header

        if recursive:
            if type(data_path) is list: # data path as a list of dir
                self.filenames = []
                for dir_p in data_path:
                    traverser = File_Traverser(dir_p, re_expr) 
                    self.filenames.extend([path for path in traverser.traverse_file_path()])
            else:  # data path as dir
                traverser = File_Traverser(data_path, re_expr)
                self.filenames.extend([path for path in traverser.traverse_file_path()])
        else:
            self.filenames = [data_path]

    def _get_dataset(self):
        return tf.contrib.data.CsvDataset(filenames=self.filenames,
                                          record_defaults=self.record_defaults,
                                          header=self.header,
                                          select_cols=self.select_cols)

    def construct_batch_feeder(self, batch_size, shuffle=True, capacity=None, min_after_dequeue=None, num_threads=1):
        '''
        Deprecate! - replaced by tf.train.Dataset
        construct tensor(s) to feed batches, to start a feeder: 
            coord = tf.train.Coordinator()
            threads = tf.train.start_queue_runners(coord=coord)
        '''
        if not capacity:
            capacity = 10 * batch_size
        if not min_after_dequeue: # minimal number after dequeue - for the level of mixing
            min_after_dequeue = batch_size

        # generate a queue to read => only single file supported now
        filename_queue = tf.train.string_input_producer(self.data_path)

        reader = tf.TextLineReader()
        _, serialized_example = reader.read(filename_queue)   # get file name & file
        input_label_tensor_pair = tf.decode_csv(serialized_example,
                                                record_defaults=self.record_defaults,)
                                                # select_cols=self.select_cols)

        if shuffle:
            batch_feeder = tf.train.shuffle_batch(input_label_tensor_pair, batch_size=batch_size, capacity=capacity, num_threads=num_threads, min_after_dequeue=min_after_dequeue, allow_smaller_final_batch=True)
        else:
            batch_feeder = tf.train.batch(input_label_tensor_pair, batch_size=batch_size, capacity=capacity, num_threads=num_threads, allow_smaller_final_batch=True)
        
        return batch_feeder # a list of tensors for corresponding input


class TF_TXT_Feeder(TF_Feeder):
    '''
    base class to construct tf.data pipeline to read, parse & feed txt data
    '''
    def __init__(self, data_path, recursive=True, file_re='.*', line_re=None, granularity='file'):
        super(TF_TXT_Feeder, self).__init__(data_path)
        self.traverser = File_Traverser(data_path, file_re)  # treat data path as dir
        self.line_re = line_re

        assert granularity in ('file', 'line')
        self.granularity = granularity

        if recursive:
            self.filenames = [path for path in self.traverser.traverse_file_path()]
        else:
            self.filenames = [self.data_path]

    def _parse_file(self, filename):
        raise NotImplementedError

    def _parse_line(self, line):
        raise NotImplementedError

    def _get_dataset(self):            
        dataset = tf.data.Dataset.from_tensor_slices(self.filenames)
        if self.granularity == 'file':
            dataset = dataset.map(self._parse_file)
        else:
            dataset = dataset.flat_map(lambda filename: tf.data.TextLineDataset(filename))
            dataset = dataset.map(self._parse_line)
        return dataset


class Gen_Feeder(object):
    '''
    base class to feed from a (list of) data dir(s)
    '''
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
        '''
        switch the split of the path list to use
        '''
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
        '''
        calculate weight
        '''
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
        '''
        transform **a 1-D list** of label into one-hot label
        '''
        height = len(label_list)
        
        label = np.zeros((height, self.class_num), dtype=int)
        label[np.arange(height), label_list] = 1

        return label

    def _get_input_label_pair(self, dirpath, name):
        raise NotImplementedError

    def iterate_data(self):
        '''
        iterate through the dataset for once
        feed examples in one file per time
        '''
        for dirpath, name in self.traverser.traverse_file():
            yield from self._get_input_label_pair(dirpath, name)

    def get_all_data(self):
        '''
        dangerous: feed all data at once
        use unless small enough & cannot partial fit
        '''
        input_list = []
        label_list = []
        for cur_input, cur_label in self.iterate_data():
            input_list.append(cur_input)
            label_list.append(cur_label)

        return input_list, label_list

    def _record_pred(self, data_dirpath, data_name, pred_func, model_name, out_subdir, overwrite):
        raise NotImplementedError
    
    def record_prediction(self, pred_func, model_name, output_dir='./Prediction', dataset_name='Data', overwrite=False, options=dict()):
        '''
        record the prediction with the same dir struct as data
        must be provided a func to predict data in one file
        '''
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
        '''
        iterate over data with corresponding meta data
        '''
        raise NotImplementedError


class Gen_CVFeeder(Gen_Feeder):
    '''
    feed data in a cross-validation fashion
    TODO: finish building the class
    '''
    def __init__(self, data_dir, class_num, fold_num, re_expr='.*', use_onehot=True):
        super(Gen_CVFeeder, self).__init__(data_dir, class_num, re_expr=re_expr, use_onehot=use_onehot, split=[1] * fold_num)
        raise NotImplementedError


class TFRecord_Constructer(object):
    '''
    base class to construct tfrecord
    '''
    def __init__(self, input_dir, output_file, re_expr='.*', recursive=True):
        self.input_dir = input_dir
        self.output_file = output_file
        self.re_expr = re_expr
        
        self.recursive = recursive  # if recursive finding into dir

    def _chk_re_expr(self, string):
        return bool(re.fullmatch(self.re_expr, string))

    def _traverse_file(self):
        assert self.recursive
        
        # traverse
        for dirpath, dirnames, files in os.walk(self.input_dir):
            for name in files:
                if self._chk_re_expr(name):
                    yield(dirpath, name)
    
    def collect_meta_data(self, meta_data_file):
        '''
        implemented in derived class: collect meta data e.g. mean, std, class statistics
        '''
        raise NotImplementedError

    def _get_raw_input_label_pair(self, dirpath, name):
        raise NotImplementedError

    def _construct_example(self, input_data_raw, label_data_raw):
        raise NotImplementedError

    def write_into_record(self):
        '''
        frame work to write into .tfrecord file
        '''        
        with tf.python_io.TFRecordWriter(self.output_file) as writer:
            for dirpath, name in self._traverse_file(): # traverse
                input_data_raw, label_data_raw = self._get_raw_input_label_pair(dirpath, name)
                example = self._construct_example(input_data_raw, label_data_raw)
                writer.write(example.SerializeToString()) # write into tfrecord
