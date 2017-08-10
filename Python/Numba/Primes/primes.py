#!/usr/bin/env python

from argparse import ArgumentParser
import sys


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute primes')
    arg_parser.add_argument('implmentation', choices=['python', 'numba'
                                                      'python_array',
                                                      'numba_array'],
                            default='python', nargs='?',
                            help='implementation to run')
    arg_parser.add_argument('--n', type=int, default=10,
                            help='number of primes')
    options = arg_parser.parse_args()
    if options.implmentation == 'python':
        from primes_vanilla import primes
    elif options.implmentation == 'numba':
        from primes_numba import primes
    results = primes(options.n)
    print(', '.join(map(str, results)))
