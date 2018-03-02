#!/usr/bin/env python

from argparse import ArgumentParser
import sys

from fac_cython import fac

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute primes')
    arg_parser.add_argument('n', type=int, default=5,
                            help='maximum value')
    options = arg_parser.parse_args()
    for i in range(options.n + 1):
        print(f'fac({i}) = {fac(i)}')
