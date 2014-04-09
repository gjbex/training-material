from array import array
import math

class Point(object):

    _id = 0
    _x = array('d')
    _y = array('d')

    def __init__(self, x, y):
        self._id = self.__class__._id
        self.__class__._id += 1
        self._x.append(x)
        self._y.append(y)

    @property
    def x(self):
        return self._x[self._id]

    @property
    def y(self):
        return self._y[self._id]

    @property
    def id(self):
        return self._id

    @classmethod
    def nr_points(cls):
        return cls._id

    def distance(self, p):
        return math.sqrt((self.x - p.x)**2 + (self.y - p.y)**2)

    def on_line(self, p, q, tol=1.0e-6):
        if math.fabs(p.x - q.x) > tol:
            a = (q.x - p.x)/(q.y - p.y)
            b = p.y - a*p.x
            return math.fabs(self.y - a*self.x - b) < tol
        else:
            return math.fabs(self.x - p.x) < tol
        
    @staticmethod
    def all_on_line(p, q, *points):
        for r in points:
            if not r.on_line(p, q):
                return False
        return True

    def __str__(self):
        return '{id}: ({x}, {y})'.format(x=self.x, y=self.y, id=self.id)

class PointMass(Point):

    def __init__(self, x, y, mass):
        super(self.__class__, self).__init__(x, y)
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
        return '{0}: {1}'.format(super(self.__class__, self).__str__(), self.mass)


