#!/usr/bin/env python

from array import array


def primes(kmax):
    p = array('i', [0]*1000)
    result = []
    if kmax > 1000:
        kmax = 1000
    k = 0
    n = 2
    while k < kmax:
        i = 0
        while i < k and n % p[i] != 0:
            i = i + 1
        if i == k:
            p[k] = n
            k = k + 1
            result.append(n)
        n = n + 1
    return result

if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='compute primes')
    arg_parser.add_argument('n', type=int, default=10, nargs='?',
                            help='number of primes')
    options = arg_parser.parse_args()
    results = primes(options.n)
    print(', '.join(map(str, results)))
