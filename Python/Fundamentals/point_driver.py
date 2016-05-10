#!/usr/bin/env python

from point import Point, PointMass


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
    p = PointMass(7, -1, 3.0)
    print(p)
    p = PointMass(1, 2)
    print(p)
    PointMass.set_default_mass(5.0)
    p = PointMass(3, 4)
    print(p)
    print(p.coords)
    p.coords = (9, 10)
    print(p.coords)

if __name__ == '__main__':
    main()
