#!/usr/bin/env python

from argparse import ArgumentParser


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='unicode test')
    arg_parser.add_argument('file', help='input file')
    options = arg_parser.parse_args()
    lines = []
    with open(options.file, 'r') as unicode_file:
        for line in unicode_file:
            line = line.rstrip()
            print('{0} -> length {1:d}'.format(line, len(line)))
            lines.append(line)
    for encoding in ['utf8', 'utf16', 'cp1252']:
        print()
        print('{0} encoding'.format(encoding))
        for line in lines:
            byte_array = line.encode(encoding)
            print('{0} -> length {1:d}'.format(byte_array, len(byte_array)))
