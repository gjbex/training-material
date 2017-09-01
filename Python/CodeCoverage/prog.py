#!/usr/bin/env python

from argparse import ArgumentParser
from functions import fac_i, fac_r

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute numer of permutations')
    arg_parser.add_argument('max_n', type=int, nargs='?', default=5,
                            help='maximum value to compute')
    arg_parser.add_argument('--no-iter', action='store_true',
                            help='do not iterate')
    arg_parser.add_argument('--impl', choices=['iterative', 'recursive'],
                            default='iterative', help='method to use')
    options = arg_parser.parse_args()
    func = fac_i if options.impl == 'iterative' else fac_r
    if options.no_iter:
        n = options.max_n
        print(f'fac({n}) = {func(n)}')
    else:
        for n in range(options.max_n + 1):
            print(f'fac({n}) = {func(n)}')


