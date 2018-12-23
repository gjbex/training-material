#!/usr/bin/env python

from argparse import ArgumentParser
import random


def main():
    arg_parser = ArgumentParser(description='testing command line arguments')
    arg_parser.add_argument('-mu', type=float,
                            default=0.0,
                            help='mean of distribution')
    arg_parser.add_argument('-sigma', type=float,
                            dest='sigma', default=1.0,
                            help='stddev of distribution')
    arg_parser.add_argument('-index', action='store_true', dest='index',
                            help='print index')
    arg_parser.add_argument('nr_numbers', metavar='n', type=int, nargs='?',
                            default=1,
                            help='number to generate')
    args = arg_parser.parse_args()
    for i in range(args.nr_numbers):
        prefix = ''
        if args.index:
            prefix = '{0}\t'.format(i + 1)
        number = random.gauss(args.mu, args.sigma)
        print('{0}{1}'.format(prefix, number))

if __name__ == '__main__':
    main()
