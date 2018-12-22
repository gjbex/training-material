#!/usr/bin/env python

from argparse import ArgumentParser
from math import cos, exp, pi, sqrt
import sys


def function(x, y):
    x0, y0 = 1.2, 0.7
    r = sqrt((x - x0)**2 + (y - y0)**2)
    return 1.0 - abs(cos(2.0*pi*r))*exp(-r)


def main():
    arg_parser = ArgumentParser(description='function to '
                                            'optimize')
    arg_parser.add_argument('--x', type=float, help='x value')
    arg_parser.add_argument('--y', type=float, help='y value')
    arg_parser.add_argument('--all', action='store_true',
                            help='print 2D function values')
    options = arg_parser.parse_args()
    if options.all:
        n = 500
        x_min, y_min, x_max, y_max = -3.0, -3.0, 3.0, 3.0
        delta_x, delta_y = (x_max - x_min)/n, (y_max - y_min)/n
        for i in range(500):
            for j in range(500):
                value = function(x_min + i*delta_x,
                                 y_min + j*delta_y)
                print(f'{value:<15.5e}', end='')
            print()
    else:
        print(f'{function(options.x, options.y):15.5e}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
