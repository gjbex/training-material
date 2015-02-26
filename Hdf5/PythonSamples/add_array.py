#!/usr/bin/env python

import sys
import numpy as np
import tables

def create_array(x_dim, y_dim):
    f = lambda x, y: x**2 + 2*x*y
    a = np.array([[f(x/float(x_dim), y/float(y_dim))
                       for y in xrange(y_dim)] for x in xrange(x_dim)])
    return a

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
