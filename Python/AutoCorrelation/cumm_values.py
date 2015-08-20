#!/usr/bin/env python

import numpy as np
import scipy.integrate
from functions import w


def cumm_values(iterator, nr_points=10, min_x=0.0, max_x=1.0):
    x_values = np.linspace(min_x, max_x, nr_points, endpoint=True)
    c_values = np.zeros(nr_points)
    n = 0
    for value in iterator:
        n += 1
        index = value <= x_values
        c_values[index] += 1.0
    return c_values/n


def cumm_function(func, nr_points=10, min_x=0.0, max_x=1.0):
    x_values = np.linspace(min_x, max_x, nr_points, endpoint=True)
    return np.array([scipy.integrate.quad(func, min_x, x)[0]
                     for x in x_values])

if __name__ == '__main__':

    from argparse import ArgumentParser
    import sys

    def main():
        arg_parser = ArgumentParser(description='compute distribution')
        arg_parser.add_argument('--points', type=int, default=10,
                                help='number of points to use')
        arg_parser.add_argument('--min', type=float, default=0.0,
                                help='minimum data value to use')
        arg_parser.add_argument('--max', type=float, default=1.0,
                                help='maximum data value to use')
        arg_parser.add_argument('--target', action='store_true',
                                help='show target distribution')
        options = arg_parser.parse_args()
        data = (float(x) for x in sys.stdin)
        x = np.linspace(options.min, options.max, options.points)
        cumms = cumm_values(data, nr_points=options.points,
                            min_x=options.min, max_x=options.max)
        if options.target:
            target = cumm_function(w, nr_points=options.points,
                                   min_x=options.min, max_x=options.max)
            print('\n'.join(['{0:.2f}\t{1:.3f}\t{2:.3f}'.format(u, v, t)
                             for u, v, t in zip(x, cumms, target)]))
        else:
            print('\n'.join(['{0:.2f}\t{1:.3f}'.format(u, v)
                             for u, v in zip(x, cumms)]))
        return 0

    status = main()
    sys.exit(status)
