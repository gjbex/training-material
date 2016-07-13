#!/usr/bin/env python

from argparse import ArgumentParser
import time
from pi_lib import compute_pi

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute pi')
    arg_parser.add_argument('n', type=int,
                            help='number of quadrature points')
    options = arg_parser.parse_args()
    start_time = time.time()
    pi = compute_pi(options.n)
    end_time = time.time()
    print('pi = {0:.6f} ({1:.6f} s)'.format(pi, end_time - start_time))
