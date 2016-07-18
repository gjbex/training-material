#!/usr/bin/env python

from argparse import ArgumentParser
import dask.array as da
from datetime import datetime
import h5py
import numpy as np
import scipy.linalg as linalg


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute and check SVD')
    arg_parser.add_argument('file', help='HDF5 file containingn matrix')
    arg_parser.add_argument('dataset', help='name of data set')
    arg_parser.add_argument('--row_chunk', type=int, default=1000,
                            help='chunk size for rows')
    arg_parser.add_argument('--col_chunk', type=int, default=1000,
                            help='chunk size for columns')
    options = arg_parser.parse_args()
    with h5py.File(options.file, mode='r') as h5file:
        start = datetime.now()
        dset = h5file[options.dataset]
        matrix = da.from_array(dset, chunks=(options.row_chunk,
                                             options.col_chunk))
        m, n = matrix.shape
        m_sum = matrix.sum().compute()
        print('avg: {0:.4f}'.format(m_sum/(m*n)))
        print('{0:d} x {1:d} matrix'.format(m, n))
        delta = datetime.now() - start
        print('HDF5 read: {0:d}.{1:06d}'.format(delta.seconds,
                                                delta.microseconds))
        start = datetime.now()
        U, s, Vh = da.linalg.svd(matrix)
        delta = datetime.now() - start
        print('linalg.svd: {0:d}.{1:06d}'.format(delta.seconds,
                                                 delta.microseconds))
        Sigma = linalg.diagsvd(s, m, n)
        start = datetime.now()
        matrix_new = da.dot(U, da.dot(Sigma, Vh)).compute()
        delta = datetime.now() - start
        print('np.dot: {0:d}.{1:06d}'.format(delta.seconds,
                                                 delta.microseconds))
        if not np.allclose(matrix, matrix_new, rtol=1.0e-11):
            sys.stderr.write('# error: matrix not reproduced\n')
