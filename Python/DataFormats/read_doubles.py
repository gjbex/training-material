#!/usr/bin/env python

from argparse import ArgumentParser, FileType
from math import sqrt
import struct


def main():
    arg_parser = ArgumentParser(description='read binary file of doubles')
    arg_parser.add_argument('--file', type=FileType('rb'), action='store',
                            dest='file', required=True,
                            help='file to read from')
    options = arg_parser.parse_args()
    with options.file as double_file:
        double_bytes = double_file.read(8)
        i = 0
        while double_bytes:
            number = struct.unpack('d', double_bytes)[0]
            print('{0:.10f} == {1:.10f}'.format(number, sqrt(i)))
            double_bytes = double_file.read(8)
            i += 1

if __name__ == '__main__':
    main()
