#!/usr/bin/env python

from argparse import ArgumentParser
import os
import sys


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='list all files with given '
                                            'extension in directory')
    arg_parser.add_argument('--dir', default='.',
                            help='directory to search')
    arg_parser.add_argument('ext', help='extension to use')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='show progress info')
    options = arg_parser.parse_args()
    for directory, _, files in os.walk(options.dir):
        if options.verbose:
            print("### checking directory '{}'".format(directory),
                  file=sys.stderr)
        for file_name in files:
            _, ext = os.path.splitext(file_name)
            if ext == options.ext:
                print(os.path.join(directory, file_name))
