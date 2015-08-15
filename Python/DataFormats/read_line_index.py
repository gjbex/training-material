#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser, FileType
    arg_parser = ArgumentParser(description='read an index line')
    arg_parser.add_argument('file', type=FileType('rb'),
                            help='file to read')
    arg_parser.add_argument('--pos', type=int, required=True,
                            help='start position of line')
    arg_parser.add_argument('--len', type=int, required=True,
                            help='line length')
    options = arg_parser.parse_args()
    options.file.seek(options.pos)
    line = options.file.read(options.len)
    print('|{0}|'.format(line))
