#!/usr/bin/env python

from ctypes import Structure, cdll, c_double, Structure
import os

class Point(Structure):
    _fields_ = [
        ('x', c_double),
        ('y', c_double)
    ]


def get_distance():
    lib = cdll.LoadLibrary(os.path.join(os.getcwd(), 'libmy_stuff.so'))
    distance = lib.distance
    distance.argtypes = [Point, Point]
    distance.restype = c_double
    return distance

if __name__ == '__main__':
    distance = get_distance()
    p1 = Point(3.0, 4.0)
    p2 = Point(-1.0, 5.0)
    d = distance(p1, p2)
    print '({0:.1f},{1:.1f}) <-> ({2:.1f},{3:.1f}) = {4:.5f}'.format(p1.x, p1.y, p2.x, p2.y, d)

