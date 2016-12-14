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

    @property
    def coords(self):
        return (self.x, self.y)

    @coords.setter
    def coords(self, value):
        self._x = value[0]
        self._y = value[1]

    def distance(self, p):
        return math.sqrt((self.x - p.x)**2 + (self.y - p.y)**2)

    def on_line(self, p, q, tol=1.0e-6):
        if not math.isclose(p.x - q.x, tol):
            a = (q.x - p.x)/(q.y - p.y)
            b = p.y - a*p.x
            return math.isclose(self.y - a*self.x - b, tol)
        else:
            return math.isclose(self.x - p.x, tol)

    @staticmethod
    def all_on_line(p, q, *points):
        for r in points:
            if not r.on_line(p, q):
                return False
        return True

    def __str__(self):
        return '({x}, {y})'.format(x=self.x, y=self.y)


class PointMass(Point):

    _default_mass = 1.0

    def __init__(self, x, y, mass=None):
        super().__init__(x, y)
        if mass:
            self._mass = float(mass)
        else:
            self._mass = self.__class__.get_default_mass()

    @property
    def mass(self):
        return self._mass

    @classmethod
    def get_default_mass(cls):
        return float(cls._default_mass)

    @classmethod
    def set_default_mass(cls, mass):
        cls._default_mass = float(mass)

    @staticmethod
    def center_of_mass(*points):
        x = 0.0
        y = 0.0
        m = 0.0
        for point in points:
            x += point.mass*point.x
            y += point.mass*point.y
            m += point.mass
        return (x/m, y/m, m)

    def __str__(self):
        return '{0}: {1}'.format(super().__str__(), self.mass)
