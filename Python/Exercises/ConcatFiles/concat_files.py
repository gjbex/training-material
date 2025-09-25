#!/usr/bin/env python

from argparse import ArgumentParser, FileType
from glob import glob
import fileinput
import sys


def main():
    arg_parser = ArgumentParser(description='concatenate data files')
    arg_parser.add_argument('-o', dest='output_file', type=FileType('w'),
                            required=True, help='output file')
    arg_parser.add_argument('-p', dest='pattern', required=True,
                            help='file glob pattern')
    options = arg_parser.parse_args()
    with options.output_file as output_file:
        is_header_written = False
        for line in fileinput.input(glob(options.pattern)):
            if fileinput.isfirstline():
                msg = "handling file '{0}'\n".format(fileinput.filename())
                sys.stderr.write(msg)
                if not is_header_written:
                    output_file.write(line)
                    is_header_written = True
            elif line.strip():
                output_file.write(line)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
