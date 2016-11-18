#!/usr/bin/env python

from argparse import ArgumentParser
import csv
import json
import random
import tables

class DataGeneratorException(Exception):

    def __init__(self):
        super().__init__()

    def __str__(self):
        return self._msg


class UnsupportedTypeError(DataGeneratorException):

    def __init__(self, value):
        super().__init__()
        self._msg = "unsupported data type '{0}'".format(value)


class UnsupportedDistributionError(DataGeneratorException):

    def __init__(self, value, num_type):
        super().__init__()
        msg = "unsupported distirbution '{0}' for type {1}"
        self._msg = msg.format(value)


class Distribution(object):

    def __init__(self, distr_func, params, n):
        self._distr = distr_func
        self._n = n
        self._current = 0
        self._params = params

    @property
    def n(self):
        return self._n

    def __iter__(self):
        self._current = 0
        return self

    def __next__(self):
        if self._current < self.n:
            self._current += 1
            return self._distr(*self._params)
        else:
            raise StopIteration()


class DistributionCreator(object):
    
    def __init__(self):
        self._distributions = {
            'int': {
                'uniform': random.randint,
            },
            'float': {
                'uniform': random.uniform,
                'gauss': random.gauss,
            }
        }

    def create(self, num_type, distr_type, params, n):
        try:
            type_distrs = self._distributions[num_type]
        except KeyError as error:
            raise UnsupportedTypeError(num_type)
        try:
            distr_func = type_distrs[distr_type]
        except KeyError as error:
            raise UnsupportedDistributionError(distr_type, num_type)
        return Distribution(distr_func, params, n)

class CsvWriter(object):

    def __init__(self, file_name, delimiter=','):
        self._file = open(file_name, 'w')
        self._writer = csv.writer(self._file, delimiter=delimiter,
                                  quoting=csv.QUOTE_MINIMAL)

    def set_headers(self, headers):
        self._writer.writerow(headers)

    def add_data(self, data):
        self._writer.writerow(data)

    def close(self):
        self._file.close()


class Hdf5Writer(object):

    def __init__(self, file_name, table_name, col_defs):
        self._file = tables.open_file(file_name, mode='w',
                                      title='generated data')
        self._typemap = {
            'int': tables.IntCol(4),
            'float': tables.Float64Col()
        }
        self._table = self._create_table(table_name, col_defs)
        self._row = self._table.row

    def _create_table(self, table_name, col_defs):
        description = {}
        for col_def in col_defs:
            description[col_def['name']] = self._typemap[col_def['type']]
        return self._file.create_table('/', table_name, description)

    def set_headers(self, headers):
        self._headers = headers

    def add_data(self, data):
        for col_name, value in zip(self._headers, data):
            self._row[col_name] = value
        self._row.append()

    def close(self):
        self._table.close()
        self._file.close()


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='generate table data')
    arg_parser.add_argument('--config', required=True,
                            help='JSON data configuration file')
    arg_parser.add_argument('--n', type=int, default=10,
                            help='number of data items to generate')
    arg_parser.add_argument('--type', choices=('csv', 'hdf5'),
                            default='csv', help='output format to generate')
    arg_parser.add_argument('--out', required=True,
                            help='output file name')
    arg_parser.add_argument('--delim', default=',',
                            help='delimiter for CSV')
    arg_parser.add_argument('--table', default='data',
                            help='name of HDF5 table to create')
    options = arg_parser.parse_args()
    with open(options.config, 'r') as config_file:
        col_defs = json.load(config_file)
    distr_creator = DistributionCreator()
    col_names = []
    distrs = []
    for col_def in col_defs:
        col_names.append(col_def['name'])
        num_type = col_def['type']
        distr_type = col_def['distribution']['type']
        distr_params = col_def['distribution']['params']
        distrs.append(distr_creator.create(num_type, distr_type,
                                           distr_params, options.n))
    if options.type == 'csv':
        writer = CsvWriter(options.out, options.delim)
    elif options.type == 'hdf5':
        writer = Hdf5Writer(options.out, options.table, col_defs)
    writer.set_headers(col_names)
    for data in zip(*distrs):
        writer.add_data(data)
    writer.close()
