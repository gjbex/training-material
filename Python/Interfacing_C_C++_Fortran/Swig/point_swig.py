#!/usr/bin/env python

import sys
from point import create_point as Point, distance


def main():
    p1 = Point(1.3, 2.5)
    p2 = Point(0.9, 2.8)
    print(distance(p1, p2))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
