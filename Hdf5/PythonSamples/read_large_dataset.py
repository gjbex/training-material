#!/usr/bin/env python

from datetime import datetime
import numpy as np
import tables

if __name__ == '__main__':
    from argparse import ArgumentParser

    arg_parser = ArgumentParser(description='read HDF5 file with a '
                                            'single large dataset, and '
                                            'compute the sum of columns')
    arg_parser.add_argument('--col', type=int, nargs='+',
                            help='column indices')
    arg_parser.add_argument('--row', type=int, nargs='+',
                            help='row indices')
    arg_parser.add_argument('--combine', action='store_true',
                            help='combine reads')
    arg_parser.add_argument('file_name', help='name of HDF5 file to raed')
    options = arg_parser.parse_args()
    with tables.openFile(options.file_name, mode='r') as h5file:
        data = h5file.root.data
        if options.col:
            start = datetime.now()
            total = 0.0
            if options.combine:
                a = data[:, options.col]
                for i in xrange(a.shape[1]):
                    total += np.sum(a[:, i])
            else:
                for col in options.col:
                    total += np.sum(data[:, col])
            delta = datetime.now() - start
            print 'reading data {0:d}.{1:06d} s'.format(delta.seconds,
                                                        delta.microseconds)
            print 'total = {0}'.format(total)
        elif options.row:
            start = datetime.now()
            total = 0.0
            if options.combine:
                a = data[options.row, :]
                for i in xrange(a.shape[0]):
                    total += np.sum(a[i, :])
            else:
                for row in options.row:
                    total += np.sum(data[row, :])
            delta = datetime.now() - start
            print 'reading data {0:d}.{1:06d} s'.format(delta.seconds,
                                                        delta.microseconds)
            print 'total = {0}'.format(total)
        else:
            start = datetime.now()
            a = np.array(data)
            delta = datetime.now() - start
            total = 0.0
            print 'reading data {0:d}.{1:06d} s'.format(delta.seconds,
                                                        delta.microseconds)
            for i in xrange(a.shape[0]):
                total += np.sum(a[i, :])
            print 'total = {0}'.format(total)
            
