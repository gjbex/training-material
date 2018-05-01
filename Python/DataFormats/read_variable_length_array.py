#!/usr/bin/env python

from argparse import ArgumentParser
from struct import unpack

def read_array(data_file, length):
    buffer = data_file.read(8*length)
    return unpack(f'{length:d}d', buffer)

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='read binary file containing '
                                            'variable length arrays')
    arg_parser.add_argument('file', help='binary file to read')
    options = arg_parser.parse_args()
    with open(options.file, 'rb') as data_file:
        buffer = data_file.read(4);
        while buffer:
            length = unpack('I', buffer)[0]
            values = read_array(data_file, length)
            value_str = ' '.join(f'{x:.2f}' for x in values)
            print(f'{length:d}: {value_str:s}')
            buffer = data_file.read(4)
