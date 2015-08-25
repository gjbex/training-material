#!/usr/bin/env python

from ctypes import cdll, c_double, c_int
import sys


def get_function():
    lib = cdll.LoadLibrary('./liblog_map.so')
    lm = lib.logistic_map
    lm.restype = c_double
    lm.argtypes = [c_double, c_double, c_int]
    return lm


def main():
    lm = get_function()
    for i in range(0, 11):
        x = float(i)/10.0
        y = lm(x, 3.2, 1000)
        print(x, y)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
