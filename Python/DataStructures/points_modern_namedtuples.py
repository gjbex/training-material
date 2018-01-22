#!/usr/bin/env python

import typing
import itertools
from math import sqrt

class Point(typing.NamedTuple):
    x: float
    y: float


def distance(p1, p2):
    '''compute the distance between two points'''
    return sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)

if __name__ == '__main__':
    fmt_str = '({0.x:.1f}, {0.y:.1f}) <-> ({1.x:.1f}, {1.y:.1f}): {2:.4f}'
    points = [Point(1.0, 2.0), Point(2.0, 1.0), Point(y=1.0, x=1.0),
              Point(y=3.0, x=1.0)]
    for p1, p2 in itertools.combinations(points, 2):
        print(fmt_str.format(p1, p2, distance(p1, p2)))
