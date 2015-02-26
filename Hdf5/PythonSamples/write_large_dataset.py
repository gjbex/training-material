#!/usr/bin/env python
 
import numpy as np                                                          
import tables

if __name__ == '__main__':
    from argparse import ArgumentParser

    arg_parser = ArgumentParser(description='create HDF5 file with a '
                                            'single large dataset')
    arg_parser.add_argument('--rows', type=int, default=1000,
                            help='number of rows of dataset')
    arg_parser.add_argument('--cols', type=int, default=1000,
                            help='number of columns of dataset')
    arg_parser.add_argument('file_name', help='name of HDF5 file to creae')
    options = arg_parser.parse_args()

    with tables.openFile(options.file_name, mode='w',
                         title='large table file') as h5file:
        val_min = 1.0
        val_max = float(options.rows)*float(options.cols)
        data = np.arange(val_min, val_max + 0.5).reshape(options.rows,
                                                         options.cols)
        h5file.createArray(h5file.root, 'data', data, 'large array')
        h5file.flush()
