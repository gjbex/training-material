#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import timeit
from array_sum import array_sum


def py_sum(a):
    total = 0.0
    for i in range(a.shape[0]):
        for j in range(a.shape[1]):
            total += a[i, j]
    return total

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute array sum using '
                                            'np.sum, cython and python')
    arg_parser.add_argument('--n', type=int, default=10000,
                            help='size (nxn array)')
    arg_parser.add_argument('--iter', type=int, default=10,
                            help='number of iterations')
    options = arg_parser.parse_args()
    a = np.ones((options.n, options.n))
    for func in [array_sum, np.sum, py_sum]:
        total = 0.0
        start_time = timeit.default_timer()
        for _ in range(options.iter):
            total += func(a)
        total_time = timeit.default_timer() - start_time
        print('{0:s}: {1:.6f} s ({2})'.format(func.__name__, total_time,
                                              total))
