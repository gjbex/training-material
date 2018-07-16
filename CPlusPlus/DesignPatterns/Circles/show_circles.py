#!/usr/bin/env python

from argparse import ArgumentParser
import matplotlib.pyplot as plt

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='plot circles in '
                                            '[0, 1] x [0, 1] '
                                            'given in a file, '
                                            'one per line as '
                                            'x y radius')
    arg_parser.add_argument('file',
                            help='file with circle definitions')
    arg_parser.add_argument('--alpha', type=float, default=0.7,
                            help='cricle transparancy')
    options = arg_parser.parse_args()
    figure, axes = plt.subplots()
    axes.set_aspect('equal')
    with open(options.file, 'r') as circle_file:
        for line in circle_file:
            x, y, radius = (float(d) for d in line.split())
            axes.add_artist(plt.Circle((x, y), radius,
                                       alpha=options.alpha))
    plt.show()
