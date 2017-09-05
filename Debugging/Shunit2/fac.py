#!/usr/bin/env python

from argparse import ArgumentParser
import sys

def fac(n):
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute number of '
                                            'permutations')
    arg_parser.add_argument('n', type=int, help='number of items')
    options = arg_parser.parse_args()
    if options.n < 0:
        sys.stderr.write('### error: argument should be positive\n')
        sys.exit(1)
    print(fac(options.n))
