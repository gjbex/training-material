#!/usr/bin/env python

from argparse import ArgumentParser
import dask.array as da
from distributed import Client
import numpy as np


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='Create two arrays, compute the sum')
    arg_parser.add_argument('--size', type=int, default=5000,
                            help='arrays size to use')
    arg_parser.add_argument('--row_chunk', type=int, default=1000,
                            help='chunk size for rows')
    arg_parser.add_argument('--col_chunk', type=int, default=1000,
                            help='chunk size for columns')
    arg_parser.add_argument('--scheduler',
                            help='scheduler as <host>:<port>')
    arg_parser.add_argument('--scheduler_port', default='8786',
                            help='scheduler port to use')
    options = arg_parser.parse_args()
    if options.scheduler:
        client = Client('{0}:{1}'.format(options.scheduler,
                                         options.scheduler_port))
    else:
        client = Client()
    print('starting client...\n')
    a = np.random.uniform(-1.0, 1.0, (options.size, options.size))
    b = np.random.uniform(-1.0, 1.0, (options.size, options.size))
    c = a + b
    print('max: {0:.4f}'.format(c.max()))
    print('min: {0:.4f}'.format(c.min()))
    print('sum: {0:.4f}'.format(c.sum()))
    A = da.from_array(a, chunks=(options.row_chunk, options.col_chunk))
    B = da.from_array(b, chunks=(options.row_chunk, options.col_chunk))
    C = A + B
    max_element = C.max()
    min_element = C.min()
    sum_elements = C.sum(axis=None)
    print('max: {0:.4f}'.format(max_element.compute()))
    print('min: {0:.4f}'.format(min_element.compute()))
    print('sum: {0:.4f}'.format(sum_elements.compute()))
