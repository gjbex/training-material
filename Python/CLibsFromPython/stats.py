#!/usr/bin/env python

from ctypes import Structure, cdll, c_double, c_int
import os


class Stats(Structure):
    _fields_ = [
        ('mean', c_double),
        ('stddev', c_double),
        ('n', c_int)
    ]


_stats = None


def get_stats(n):
    global _stats
    if _stats is None:
        lib = cdll.LoadLibrary(os.path.join(os.getcwd(), 'libmy_stuff.so'))
        _stats = lib.stats
        _stats.restype = Stats
    _stats.argtypes = [c_double * n, c_int]
    return _stats


def compute_stats(*data):
    n = len(data)
    stats = get_stats(n)
    array_type = c_double * n
    d = array_type(*data)
    return stats(d, n)

if __name__ == '__main__':
    str_tmpl = 'mean = {0:f}, stddev = {1:f}, n = {2}'
    s = compute_stats(1.0, 2.5, 2.0, 3.0, 3.5)
    print(str_tmpl.format(s.mean, s.stddev, s.n))
    s = compute_stats(1.0, 2.5, 2.0, 3.0, 3.5, -1.0, -3.0)
    print(str_tmpl.format(s.mean, s.stddev, s.n))
    s = compute_stats(3.0, 4.0, 5.0)
    print(str_tmpl.format(s.mean, s.stddev, s.n))
