#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import pandas as pd
import re
import sys


class AgtException(Exception):
    '''Base class for Agt file parser exceptions.'''

    def __str__(self):
        return self.message


class NoAgtDataSectionError(AgtException):
    '''Exception raised when no data header is present in the file.'''

    def __init__(self):
        '''Constructor, sets message'''
        self.message = 'No data section found'


class AgtDataError(AgtException):
    '''Exception raised when a problem with the data is detected.'''

    def __init__(self, msg):
        '''Constructor that sets message.'''
        self.message = msg


class AgtParser(object):
    '''Parser for agt files that contain sensor data, i.e., timestamps,
    temerature, and pressure. These files also contain meta-inforamtion
    that is ignored.
    '''

    def __init__(self, dt_fmt='%Y/%m/%d %H:%M:%S', sep=';',
                 data_header='[Data]', footer_header='END OF DATA',
                 columns=('pressure', 'temperature')):
        '''Constructor for a new parser, optionally specify a timestamp
        format.
        '''
        self._dt_fmt = dt_fmt
        self._data_header = data_header
        self._footer_header = footer_header
        self._columns = columns
        self._sep = sep
        self._nr_cols = 3
        self._current_line = None

    def parse(self, file_name, encoding='latin-1'):
        '''parse the file with the given name, return a pandas
        DataFrame with the timestamp as index, and the pressure and
        temperature as columns.
        '''
        self._current_line = 0
        with open(file_name, 'r', encoding=encoding) as agt_file:
            self._parse_meta_data(agt_file)
            df = self._parse_data(agt_file)
            self._parse_footer(agt_file)
            return df

    def _parse_meta_data(self, agt_file):
        '''parse the meta data, and leaving the file handle pointing to
        the start of the data section'''
        position = 0
        for line in agt_file:
            self._current_line += 1
            position += len(line)
            if line.startswith(self._data_header):
                agt_file.seek(position)
                break
        else:
            raise NoAgtDataSectionError()

    def _read_data(self, agt_file, nr_lines):
        '''erad the actual data, this is a hand written parser.'''
        indices = []
        measurements = np.empty((nr_lines, 2))
        for line_nr in range(nr_lines):
            self._current_line += 1
            line = agt_file.readline().rstrip()
            data = line.split(self._sep)
            if len(data) != self._nr_cols:
                msg = "ine {0:d} is invalid: '{1}'"
                raise AgtDataError(msg.format(self._current_line, line))
            try:
                indices.append(pd.datetime.strptime(data[0], self._dt_fmt))
                measurements[line_nr][0] = float(data[1])
                measurements[line_nr][1] = float(data[2])
            except ValueError as error:
                msg = 'line {0:d}: {1}'
                raise AgtDataError(msg.format(self._current_line, error))
        df = pd.DataFrame(measurements, index=indices,
                          columns=self._columns)
        df.index.name = 'timestamp'
        return df

    def _parse_data(self, agt_file):
        '''parse the data section, the file points is at the line below
        the header'''
        nr_lines_str = agt_file.readline()
        match = re.match(r'(\d+)', nr_lines_str)
        if not match:
            msg = "line {0:d}: invalid number of measurements '{1}'"
            raise AgtDataError(msg.format(self._current_line, nr_lines_str))
        nr_lines = int(match.group(1))
        self._current_line += 1
# ignore header line
        agt_file.readline()
        self._current_line += 1
        return self._read_data(agt_file, nr_lines)

    def _parse_footer(self, agt_file):
        '''parse footer, i.e., file content after data.'''
        line = agt_file.readline().rstrip()
        self._current_line += 1
        if not (line and line.startswith(self._footer_header)):
            msg = "line {0:d}: invalid footer '{1}'"
            raise AgtDataError(msg.format(self._current_line, line))


class AgtPandasParser(AgtParser):
    '''Parser for agt files that contain sensor data, i.e., timestamps,
    temerature, and pressure. These files also contain meta-inforamtion
    that is ignored.
    '''

    def _read_data(self, agt_file, nr_lines):
        '''read data using pandas methods'''
        def dt_conv(dt):
            return pd.datetime.strptime(dt, self._dt_fmt)
        df = pd.read_csv(agt_file, sep=self._sep, converters={0: dt_conv},
                         names=(['timestamp'] + list(self._columns)),
                         nrows=nr_lines)
        df.set_index('timestamp', inplace=True)
        self._current_line += nr_lines
        return df

    def _parse_footer(self, agt_file):
        '''parse footer, i.e., file content after data.'''
# Since the pandas read_csv method swallows an extra line, this parser needs
# to check for an empty footer
        line = agt_file.readline().rstrip()
        self._current_line += 1
        if line:
            msg = "line {0:d}: invalid footer '{1}'"
            raise AgtDataError(msg.format(self._current_line, line))


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='parse AGT files, and print '
                                            'part of data')
    arg_parser.add_argument('file', help='file to parse')
    arg_parser.add_argument('--dt_fmt', default='%Y/%m/%d %H:%M:%S',
                            help='timestamp format to use')
    options = arg_parser.parse_args()
    agt_parser = AgtParser(dt_fmt=options.dt_fmt)
    try:
        df = agt_parser.parse(options.file)
        print(df.head())
        print('...')
        print(df.tail())
    except AgtException as error:
        print('Parse error at {0}'.format(error), file=sys.stderr)
    agt_parser = AgtPandasParser(dt_fmt=options.dt_fmt)
    df = agt_parser.parse(options.file)
    print(df.head())
    print('...')
    print(df.tail())
