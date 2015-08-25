#!/usr/bin/env python

from math import floor
import numpy as np
import scipy.integrate


def bin_values(iterator, nr_bins=10, min_x=0.0, max_x=1.0):
    bins = [0 for _ in range(nr_bins)]
    n = 0
    for x in iterator:
        n += 1
        index = int(floor(nr_bins*(x - min_x)/(max_x - min_x)))
        bins[index] += 1
    return [x/n for x in bins]


def dist(func, x):
    temp = [0.0] + [scipy.integrate.quad(func, 0.0, u)[0] for u in x]
    return [temp[i] - temp[i - 1] for i in range(1, len(temp))]

if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    from functions import w

    def main():
        arg_parser = ArgumentParser(description='compute distribution')
        arg_parser.add_argument('--bins', type=int, default=10,
                                help='number of bins to use')
        arg_parser.add_argument('--min', type=float, default=0.0,
                                help='minimum data value to use')
        arg_parser.add_argument('--max', type=float, default=1.0,
                                help='maximum data value to use')
        arg_parser.add_argument('--target', action='store_true',
                                help='show target distribution')
        options = arg_parser.parse_args()
        data = (float(x) for x in sys.stdin)
        bins = bin_values(data, nr_bins=options.bins,
                          min_x=options.min, max_x=options.max)
        x_min = options.min + (options.max - options.min)/options.bins
        x = np.linspace(x_min, options.max, options.bins)
        if options.target:
            target = dist(w, x)
            print('\n'.join(['{0:.2f}\t{1:.3f}\t{2:.3f}'.format(u, v, t)
                             for u, v, t in zip(x, bins, target)]))
        else:
            print('\n'.join(['{0:.2f}\t{1:.3f}'.format(u, v)
                             for u, v in zip(x, bins)]))
        return 0

    status = main()
    sys.exit(status)
