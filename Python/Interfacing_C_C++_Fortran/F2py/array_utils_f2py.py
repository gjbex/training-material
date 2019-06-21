#!/usr/bin/env python

import sys
import numpy
from array_utils import array_utils


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 3
    print(array_utils.sum_array(list(range(1, n + 1))))
    print(array_utils.sum_array(numpy.arange(1.0, float(n) + 1.0)))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
