#!/usr/bin/env python

from argparse import ArgumentParser
import random
import sys
from joblib import Parallel, delayed

nr_hits = 0


def try_hits(nr_trials):
    global nr_hits
    my_hits = 0
    for _ in range(nr_trials):
        x = random.random()
        y = random.random()
        if x**2 + y**2 <= 1.0:
            my_hits += 1
    nr_hits += my_hits

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute pi')
    arg_parser.add_argument('-n', dest='nr_trials', type=int, default=10000,
                            help='number of trials')
    arg_parser.add_argument('-j', dest='nr_jobs', type=int, default=1,
                            help='number of threads')
    arg_parser.add_argument('-p', dest='nr_packets', type=int, default=5,
                            help='number of work packets')
    options = arg_parser.parse_args()
    Parallel(n_jobs=-1)(
        delayed(try_hits)(options.nr_trials) for _ in range(options.nr_packets)
    )
    pi = 4.0*float(nr_hits)/(options.nr_trials*options.nr_packets)
    print('{0:.10f}'.format(pi))
    sys.exit(0)
