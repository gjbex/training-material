#!/usr/bin/env python

import math


class Point(object):

    def __init__(self, x, y):
        self._x = float(x)
        self._y = float(y)

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    def distance(self, p):
        return math.sqrt((self.x - p.x)**2 + (self.y - p.y)**2)

    def on_line(self, p, q, tol=1.0e-6):
        if math.fabs(p.x - q.x) <= tol:
            return math.fabs(self.x - p.x) < tol
        a = (q.x - p.x)/(q.y - p.y)
        b = p.y - a*p.x
        return math.fabs(self.y - a*self.x - b) < tol

    def __str__(self):
        return '({x}, {y})'.format(x=self.x, y=self.y)


class PointMass(Point):

    default_mass = 1.0

# Using default_mass as default value in constructor wouldn't work since
# the default_mass's value is retained that it has when it is defined.
    def __init__(self, x, y, mass=None):
        super().__init__(x, y)
        self._mass = float(mass) if mass else PointMass.default_mass

    @property
    def mass(self):
        return self._mass

    @classmethod
    def set_default_mass(cls, mass):
        cls.default_mass = mass

    def __str__(self):
        return '{0}: {1}'.format(super().__str__(), self.mass)


if __name__ == '__main__':
    p = PointMass(1, 3)
    q = PointMass(2, 3, 5)
    print(p, q)
    PointMass.set_default_mass(3)
    r = PointMass(3, 4)
    print(r)
