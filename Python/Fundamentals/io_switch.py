#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser
    from io import StringIO
    import sys
    arg_parser = ArgumentParser(description='I/O test')
    arg_parser.add_argument('-o', dest='output', help='output file')
    options = arg_parser.parse_args()
    str_io = StringIO()
    for line in ['abc', 'def', 'ghi']:
        str_io.write(line + '\n')
    output = open(options.output, 'w') if options.output else sys.stdout
    output.write(str_io.getvalue())
    if options.output:
        output.close()
