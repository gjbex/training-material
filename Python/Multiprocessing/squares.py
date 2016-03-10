#!/usr/bin/env python

from multiprocessing import Pool
import sys


def f(x):
    return x*x


def main():
    p = Pool(5)
    results = p.map(f, [1, 3, 7])
    print(results)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
