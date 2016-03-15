#!/usr/bin/env python

import sys
import numpy as np
import tables

def main():
    h5file = tables.openFile('test.h5', mode='r')
    higgs = h5file.root.fields.higgs
    print 'sum = {0:.7f}'.format(np.sum(higgs))
    h5file.close()
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

