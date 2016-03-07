#!/usr/bin/env python

from argparse import ArgumentParser
import math
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
import multiprocessing
import random
import sys


def partial_pi(args=(1000, )):
    nr_tries = args[0]
    nr_hits = 0
    for _ in range(nr_tries):
        x = random.random()
        y = random.random()
        if x**2 + y**2 < 1.0:
            nr_hits += 1
    return 4.0*nr_hits/nr_tries


def compute_pi(nr_tries=10000, pool_size=None, constructor=None):
    if not constructor:
        executor = ProcessPoolExecutor(max_workers=pool_size)
    else:
        executor = constructor(max_workers=pool_size)
    args = [(nr_tries//pool_size, )
            for _ in range(pool_size)]
    results = executor.map(partial_pi, args)
    if not pool_size:
        pool_size = multiprocessing.cpu_count()
    return sum(results)/pool_size


def main():
    arg_parser = ArgumentParser(description='compute pi')
    arg_parser.add_argument('--p', dest='pool_size', type=int,
                            default=1, help='pool size')
    arg_parser.add_argument('--n', dest='nr_tries', type=int,
                            default=1, help='number of tries')
    arg_parser.add_argument('--t', default='processes', dest='type',
                            choices=['processes', 'threads'],
                            help='Either use processes or treads')
    options = arg_parser.parse_args()
    if options.type:
        if options.type == 'processes':
            constructor = ProcessPoolExecutor
        else:
            constructor = ThreadPoolExecutor
        my_pi = compute_pi(options.nr_tries, options.pool_size, constructor)
    else:
        my_pi = compute_pi(options.nr_tries, options.pool_size)
    print('computed pi = {0:.15f}'.format(my_pi))
    print('exact pi    = {0:.15f}'.format(math.pi))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
