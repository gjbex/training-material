#!/usr/bin/env python

from argparse import ArgumentParser
import random
import time


def init_matrix(n, value=None):
    m = []
    for i in range(n):
        m.append([])
        for _ in range(n):
            if value is not None:
                m[i].append(value)
            else:
                m[i].append(random.random())
    return m


def matmul(a, b, c):
    n = len(a)
    for i in range(n):
        for j in range(n):
            for k in range(n):
                c[i][j] += a[i][k]*a[k][j]


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
    print('initializing c...')
    start_time = time.time()
    c = init_matrix(args.n, 0.0)
    end_time = time.time()
    print(('initialized c: {0} s'.format(end_time - start_time)))
    print('multiplying...')
    start_time = time.time()
    matmul(a, b, c)
    end_time = time.time()
    print(('multiplied: {0} s'.format(end_time - start_time)))

if __name__ == '__main__':
    main()
