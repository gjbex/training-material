#!/usr/bin/env python

from argparse import ArgumentParser
import random, sys

def try_hit():
    x = random.random()
    y = random.random()
    if x**2 + y**2 <= 1.0:
        return 1
    else:
        return 0

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute pi')
    arg_parser.add_argument('-n', dest='nr_trials', type=int, default=10000,
                            help='number of trials')
    options = arg_parser.parse_args()
    nr_hits = 0
    for _ in xrange(options.nr_trials):
        nr_hits += try_hit()
    pi = 4.0*float(nr_hits)/options.nr_trials
    print '{0:.10f}'.format(pi)
    sys.exit(0)

