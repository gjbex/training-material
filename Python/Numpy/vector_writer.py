#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import time


def create_vector(n):
    v = np.empty((n, ))
    x = 1.0e-10
    delta = 1.0e-10
    for i in range(n):
        v[i] = x
        x += delta
    return v

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='write a vector to file')
    arg_parser.add_argument('file', help='file name for output')
    arg_parser.add_argument('--n', type=int, default=10,
                            help='vector length')
    arg_parser.add_argument('--format', choices=['binary', 'text'],
                            default='binary', help='format to write data')
    options = arg_parser.parse_args()
    v = create_vector(options.n)
    t_start = time.time()
    if options.format == 'binary':
        v.tofile(options.file)
    elif options.format == 'text':
        v.tofile(options.file, sep='\n', format='%.10e')
    t_stop = time.time()
    print('time {0:.6f}'.format(t_stop - t_start))
