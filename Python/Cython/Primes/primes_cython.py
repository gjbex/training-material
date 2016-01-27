#!/usr/bin/env python

from primes import primes


if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='compute primes')
    arg_parser.add_argument('n', type=int, default=10, nargs='?',
                            help='number of primes')
    options = arg_parser.parse_args()
    results = primes(options.n)
    print(', '.join(map(str, results)))
