#!/usr/bin/env python

import sys
import numpy as np
import tables

def create_array(x_dim, y_dim):
    f = lambda x, y: x**2 + 2*x*y
    x = np.linspace(0.0, 1.0, x_dim, endpoint=False)
    y = np.linspace(0.0, 1.0, y_dim, endpoint=False)
    X, Y = np.meshgrid(x, y, indexing='ij')
    return f(X, Y)

def add_array(name):
    with tables.openFile(name, mode='a') as h5file:
        fields_group = h5file.createGroup(h5file.root, 'fields',
                                          'system's fields')
        field = create_array(100, 200)
        h5file.createArray(fields_group, 'higgs', field, 'Higgs field')
        h5file.flush()

def main():
    h5file = add_array('test.h5')
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
