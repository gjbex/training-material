#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import time


def init_matrix(n, value=None):
    if value is None:
        m = np.random.uniform(0.0, 1.0, (n, n))
    else:
        m = np.fromfunction(lambda i, j: value, (n, n))
    return m


def main():
    arg_parser = ArgumentParser(description='matrix multiplication timer')
    arg_parser.add_argument('-n', type=int, default=5,
                            help='matrix dimension')
    args = arg_parser.parse_args()
    print('initializing a...')
    start_time = time.time()
    a = init_matrix(args.n)
    end_time = time.time()
    print(('initialized a: {0} s'.format(end_time - start_time)))
    print('initializing b...')
    start_time = time.time()
    b = init_matrix(args.n)
    end_time = time.time()
    print(('initialized b: {0} s'.format(end_time - start_time)))
    print('multiplying...')
    start_time = time.time()
    c = np.dot(a, b)
    end_time = time.time()
    print(('multiplied: {0} s'.format(end_time - start_time)))

if __name__ == '__main__':
    main()
