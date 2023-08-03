#!/usr/bin/env python

from argparse import ArgumentParser
from array import array


@profile
def primes(kmax):
    max_size = 1000000
    p = array('i', [0]*max_size)
    result = []
    kmax = min(kmax, max_size)
    k = 0
    n = 2
    while k < kmax:
        i = 0
        while i < k and n % p[i] != 0:
            i += 1
        if i == k:
            p[k] = n
            k += 1
            result.append(n)
        n = n + 1
    return result


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute primes')
    arg_parser.add_argument('--n', type=int, default=10,
                            help='number of primes')
    arg_parser.add_argument('--quiet', action='store_true',
                            help='do not write output')
    options = arg_parser.parse_args()
    results = primes(options.n)
    if not options.quiet:
        print(', '.join(map(str, results)))
