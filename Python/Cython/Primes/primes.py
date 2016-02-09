#!/usr/bin/env python

from argparse import ArgumentParser
import sys


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute primes')
    arg_parser.add_argument('version', help='version to run')
    arg_parser.add_argument('--n', type=int, default=10,
                            help='number of primes')
    options = arg_parser.parse_args()
    if options.version == 'python':
        from primes_vanilla import primes
    elif options.version == 'cython':
        from primes_cython import primes
    else:
        msg = '### error: unknown primes version "{0}"'
        print(msg.format(options.version), file=sys.stderr)
        sys.exit(1)
    results = primes(options.n)
    print(', '.join(map(str, results)))
