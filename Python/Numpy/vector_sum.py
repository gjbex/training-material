#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import time


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='reae vector from file and '
                                            'compute the sum of its '
                                            'components')
    arg_parser.add_argument('file', help='file to read')
    arg_parser.add_argument('--format', choices=['binary', 'text'],
                            default='binary', help='file format')
    options = arg_parser.parse_args()
    t_start = time.time()
    if options.format == 'binary':
        v = np.fromfile(options.file)
    elif options.format == 'text':
        v = np.fromfile(options.file, sep='\n')
    t_stop = time.time()
    print('{0:.10e} ({1:d} elements)'.format(np.sum(v), v.shape[0]))
    print('time {0:.6f}'.format(t_stop - t_start))
