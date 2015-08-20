#!/usr/bin/env python

from ctypes import cdll, c_int, c_double
import os
import sys


def get_log_map():
    lib = cdll.LoadLibrary(os.path.join(os.getcwd(), 'libmy_stuff.so'))
    log_map = lib.log_map
    log_map.argtypes = [c_double, c_double, c_int]
    log_map.restype = c_double
    return log_map


def main():
    log_map = get_log_map()
    x = log_map(0.5, 3.2, 1000)
    print(x)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
