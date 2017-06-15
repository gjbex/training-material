#!/usr/bin/env python

from itertools import product as iproduct
from itertools import count as icount
import sys


def main():
    print('case', 'condition', 'temperature')
    for i, data in enumerate(iproduct(range(1, 4),
                                      map(lambda x: 0.5*x,
                                          range(-1, 2)))):
         print(i + 1, *data)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
