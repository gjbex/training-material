#!/usr/bin/env python

from argparse import ArgumentParser
import math
import multiprocessing as mp
import random
import sys


def partial_pi(nr_tries, p_sum):
    nr_hits = 0
    for _ in range(nr_tries):
        x = random.random()
        y = random.random()
        if x**2 + y**2 < 1.0:
            nr_hits += 1
    with p_sum.get_lock():
        p_sum.value += 4.0*nr_hits/nr_tries


def compute_pi(nr_tries=10000, pool_size=1):
    ctx = mp.get_context('forkserver')
    p_sum = ctx.Value('d', 0.0)
    processes = [ctx.Process(target=partial_pi,
                             args=(nr_tries//pool_size, p_sum))
                 for _ in range(pool_size)]
    for process in processes:
        process.start()
    for process in processes:
        process.join()
    return p_sum.value/pool_size


def main():
    arg_parser = ArgumentParser(description='compute pi')
    arg_parser.add_argument('--p', dest='pool_size', type=int,
                            default=1, help='pool size')
    arg_parser.add_argument('--n', dest='nr_tries', type=int,
                            default=1, help='number of tries')
    options = arg_parser.parse_args()
    my_pi = compute_pi(options.nr_tries, options.pool_size)
    print('computed pi = {0:.15f}'.format(my_pi))
    print('exact pi    = {0:.15f}'.format(math.pi))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
