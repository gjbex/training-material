#!/usr/bin/env python

from point_2 import Point, PointMass


def main():
    p = Point(3, 4)
    q = Point(-2, 5)
    print(p.x, p.y)
    print(p, q)
    print(p.distance(q))
    v = Point(9, 9)
    w = Point(10, 10)
    points = [Point(i, i) for i in range(5)]
    if Point.all_on_line(v, w, *points):
        print('on a line')
    print(Point.nr_points())
    p = PointMass(7, -1, 3.0)
    print(p)

if __name__ == '__main__':
    main()
