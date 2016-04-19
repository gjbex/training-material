#!/usr/bin/env python
'''dataset implements a poor man's version of pandas data frames, it is
   only intended to illustrate a number of concepts about iterators
   and can be used when dependencies on third party libraries should
   be avoided'''

import collections
import operator

ColumnDef = collections.namedtuple('ColumnSpecs', ['name', 'type'])


class DatasetError(Exception):
    '''Base class for Dataset exceptions'''

    pass


class DataLenError(DatasetError):
    '''Exception indicating that a list of data is being appended with
       a length different from the number of headers of the data set'''

    pass


class ConversionError(DatasetError):
    '''Exception indicating that a type conversion failed, i.e., a
       value is appended that can not be converted to its column's
       type'''

    pass


class ColumnOverwriteError(DataLenError):
    '''Exception indicating that a new column would overwrite an
       existing one.'''

    pass


class UndefinedColumnError(DataLenError):
    '''Exception indicating that a column does not exist in the dataset'''

    pass


class ComputeError(DataLenError):
    '''Exception indicating that a computation failed'''

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
    def nr_columns(self):
        '''returns number of columns in the dataset'''
        return len(self._headers)

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
            try:
                value = self._convert(header, data[i])
            except ValueError as error:
                msg = 'type conversion failed: {0}'.format(str(error))
                raise ConversionError(msg)
            self._data[header].append(value)
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
            if col_def.name in self._headers:
                msg = 'column {0} already exists'.format(col_def.name)
                raise ColumnOverwriteError(msg)
            self._data[col_def.name] = []
        for name in args:
            if name not in self._headers:
                msg = 'no column {0} in dataset'.format(name)
                raise UndefinedColumnError(msg)
        arg_idx = tuple(self._headers.index(name) for name in args)
        selector = operator.itemgetter(*arg_idx)
        names = [col_def.name for col_def in col_defs]
        for row in self:
            args = selector(row)
            try:
                values = function(*args)
            except Exception as error:
                args_str = ', '.join([str(arg) for arg in args])
                msg = "computation for '{0}' failed: {1}".format(args_str,
                                                                 str(error))
                raise ComputeError(msg)
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
    try:
        data.append(['bla'] * data.nr_columns)
    except Exception as error:
        print('### error: {0}'.format(error))
