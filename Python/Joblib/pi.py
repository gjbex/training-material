#!/usr/bin/env python

from argparse import ArgumentParser
import random
import sys


def try_hits(nr_trials):
    nr_hits = 0
    for _ in range(nr_trials):
        x = random.random()
        y = random.random()
        if x**2 + y**2 <= 1.0:
            nr_hits += 1
    return nr_hits

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute pi')
    arg_parser.add_argument('-n', dest='nr_trials', type=int, default=10000,
                            help='number of trials')
    options = arg_parser.parse_args()
    nr_hits = try_hits(options.nr_trials)
    pi = 4.0*float(nr_hits)/options.nr_trials
    print('{0:.10f}'.format(pi))
    sys.exit(0)
