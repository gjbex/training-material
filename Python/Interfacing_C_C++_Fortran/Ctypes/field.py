#!/usr/bin/env python

from ctypes import cdll, c_int, c_double
import os
import sys


def get_log_map():
    lib = cdll.LoadLibrary(os.path.join(os.getcwd(), 'liblog_map.so'))
    log_map = lib.logistic_map
    log_map.argtypes = [c_double, c_double, c_int]
    log_map.restype = c_double
    return log_map


def main():
    log_map = get_log_map()
    r0 = 2.2
    r_delta = 0.1
    nr_r_values = 15
    sys.stdout.write('# r')
    for j in range(nr_r_values):
        r = r0 + r_delta*j
        sys.stdout.write('\t{0:.2f}'.format(r))
    sys.stdout.write('\n')
    nr_points = 100
    for i in range(1, nr_points):
        x0 = float(i)/nr_points
        sys.stdout.write('{0:.2f}'.format(x0))
        for j in range(nr_r_values):
            r = r0 + r_delta*j
            sys.stdout.write('\t{0:.4f}'.format(log_map(x0, r, 100000)))
        sys.stdout.write('\n')
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
