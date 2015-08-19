#!/usr/bin/env python

from argparse import ArgumentParser
import math
import multiprocessing
import sys


def partial_pi(args=(0.0, 1.0, 0.01)):
    a, b, delta = args
    part_pi = 0.0
    x = a + 0.5*delta
    while x <= b:
        part_pi += 4.0/(1.0 + x*x)
        x += delta
    return part_pi*delta


def compute_pi(delta=0.01, pool_size=None, intervals=None):
    if not pool_size:
        pool_size = multiprocessing.cpu_count()
    if not intervals:
        intervals = pool_size
    pool = multiprocessing.Pool(processes=pool_size)
    interval = 1.0/intervals
    args = [(i*interval, (i + 1)*interval - delta, delta)
            for i in range(intervals)]
    results = pool.map(partial_pi, args)
    return sum(results)


def main():
    arg_parser = ArgumentParser(description='compute pi')
    arg_parser.add_argument('-d', dest='delta', type=float,
                            default=0.01, help='resolution for quadrature')
    arg_parser.add_argument('-p', dest='pool_size', type=int,
                            default=1, help='pool size')
    arg_parser.add_argument('-n', dest='intervals', type=int,
                            default=1, help='number of intervals')
    options = arg_parser.parse_args()
    my_pi = compute_pi(options.delta, options.pool_size,
                       options.intervals)
    print('computed pi = {0:.15f}'.format(my_pi))
    print('exact pi    = {0:.15f}'.format(math.pi))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
