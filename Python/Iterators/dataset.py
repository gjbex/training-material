#!/usr/bin/env python

import collections
import operator

ColumnDef = collections.namedtuple('ColumnSpecs', ['name', 'type'])


class DataLenError(Exception):
    '''Exception indicating that a list of data is being appended with
       a length different from the number of headers of the data set'''

    pass


class Dataset(object):
    '''Class representing data sets'''

    def __init__(self, col_defs):
        '''Constructor that optonally takes the data set headers'''
        self._headers = [col_def.name for col_def in col_defs]
        self._type_map = {col_def.name: col_def.type
                          for col_def in col_defs}
        self._data = {header: [] for header in self._headers}
        self._nr_data = 0
        self._next = 0

    @property
    def headers(self):
        '''get the list of headers for the data set'''
        return list(self._headers)

    @property
    def column_defs(self):
        '''retrieve the column definitions of the dataset'''
        col_defs = []
        for header in self._headers:
            col_defs.append(ColumnDef(header, self._type_map[header]))
        return col_defs

    def __len__(self):
        '''retrieve the length of the data set'''
        return self._nr_data

    def _convert(self, header, value):
        '''convert the value to the appropriate data type'''
        return self._type_map[header](value)

    def append(self, data):
        '''append a row of data to the set'''
        if len(data) != len(self._headers):
            msg = '{0:d} headers, {1:d} items'.format(len(self._headers),
                                                      len(data))
            raise DataLenError(msg)
        for i, header in enumerate(self._headers):
            self._data[header].append(self._convert(header, data[i]))
        self._nr_data += 1

    def __iter__(self):
        '''iterator over the data values in the data set, each returning
           a list ordered according to the headers of the data set'''
        self._RowTuple = collections.namedtuple('RowTuple', self._headers)
        self._next = 0
        return self

    def __next__(self):
        '''return next data value when dataset is used as an iterator'''
        if self._next < self._nr_data:
            values = self._RowTuple._make((self._data[header][self._next]
                                           for header in self._headers))
            self._next += 1
            return values
        else:
            self._next = 0
            raise StopIteration

    def compute(self, col_defs, args, function):
        '''perform a computation producing extra columns by applying a
           function using the specified argument names'''
        for col_def in col_defs:
            self._data[col_def.name] = []
        arg_idx = tuple(self._headers.index(name) for name in args)
        selector = operator.itemgetter(*arg_idx)
        names = [col_def.name for col_def in col_defs]
        for row in self:
            values = function(*selector(row))
            for name, value in zip(names, values):
                self._data[name].append(value)
        for col_def in col_defs:
            self._headers.append(col_def.name)
            self._type_map[col_def.name] = col_def.type

    def __str__(self):
        '''create string representation of the data set'''
        str_repr = ', '.join(self._headers)
        for row in self:
            str_repr += '\n' + ', '.join([str(x) for x in row])
        return str_repr


if __name__ == '__main__':
    data = Dataset([
        ColumnDef('x', int),
        ColumnDef('y', int),
        ColumnDef('z', int),
    ])
    for x in range(10):
        data.append((x, x**2, x**3))
    print(data)
    data.compute([ColumnDef('sum', int), ColumnDef('prod', int)], ['x', 'y'],
                 lambda x, y: (x + y, x*y))
    print(data)
    for row in data:
        print('{0:d} + {1:d} = {2:d}'.format(row.x, row.y, row.sum))
    print('{0:d} data items'.format(len(data)))
    data.compute([ColumnDef('substr', int)], ['x', 'y'],
                 lambda x, y: (y - x, ))
    print(data)
