import math


class Point(object):

    _id = 0

    def __init__(self, x, y):
        self._x = x
        self._y = y
        self._id = Point._id
        self.__class__._id += 1

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def id(self):
        return self._id

    @classmethod
    def nr_points(cls):
        return cls._id

    def distance(self, p):
        return math.sqrt((self.x - p.x)**2 + (self.y - p.y)**2)

    def on_line(self, p, q, tol=1.0e-6):
        if math.fabs(p.x - q.x) <= tol:
            return math.fabs(self.x - p.x) < tol
        a = (q.y - p.y)/(q.x - p.x)
        b = p.y - a*p.x
        return math.fabs(self.y - a*self.x - b) < tol

    @staticmethod
    def all_on_line(p, q, *points):
        return all(r.on_line(p, q) for r in points)

    def __str__(self):
        return '{id}: ({x}, {y})'.format(x=self.x, y=self.y, id=self.id)


class PointMass(Point):

    def __init__(self, x, y, mass):
        super().__init__(x, y)
        self._mass = mass

    @property
    def mass(self):
        return self._mass

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
