#!/usr/bin/env python

from argparse import ArgumentParser
import sys
from comp_pi import compute_pi


def main():
    arg_parser = ArgumentParser(description='compute pi using Fortran '
                                'function')
    arg_parser.add_argument('n', default=1000, nargs='?',
                            help='number of random points')
    options = arg_parser.parse_args()
    print(compute_pi(options.n))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
