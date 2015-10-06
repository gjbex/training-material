#!/usr/bin/env python

from argparse import ArgumentParser
from datetime import datetime
import numpy as np
import scipy.linalg as linalg
import tables


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute and check SVD')
    arg_parser.add_argument('file', help='HDF5 file containingn matrix')
    arg_parser.add_argument('dataset', help='name of data set')
    options = arg_parser.parse_args()
    with tables.openFile(options.file, mode='r') as h5file:
        start = datetime.now()
        matrix = h5file.get_node(h5file.root, name=options.dataset)
        m, n = matrix.shape
        print('{0:d} x {1:d} matrix'.format(m, n))
        delta = datetime.now() - start
        print('HDF5 read: {0:d}.{1:06d}'.format(delta.seconds,
                                                delta.microseconds))
        start = datetime.now()
        U, s, Vh = linalg.svd(matrix)
        delta = datetime.now() - start
        print('linalg.svd: {0:d}.{1:06d}'.format(delta.seconds,
                                                 delta.microseconds))
        Sigma = linalg.diagsvd(s, m, n)
        start = datetime.now()
        matrix_new = np.dot(U, np.dot(Sigma, Vh))
        delta = datetime.now() - start
        print('np.dot: {0:d}.{1:06d}'.format(delta.seconds,
                                                 delta.microseconds))
        if not np.allclose(matrix, matrix_new, rtol=1.0e-11):
            sys.stderr.write('# error: matrix not reproduced\n')
