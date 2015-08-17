from Shape import Shape
from Colored import Colored


class Circle(Shape, Colored):

    def __init__(self, x, y, r, color):
        super(Circle, self).__init__('circle')
        self._x = x
        self._y = y
        self._r = r
        self.color = color

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def r(self):
        return self._r

    def __str__(self):
        return '{name} ({x}, {y}: {r})'.format(name=self.name, x=self.x,
                                               y=self.y, r=self.r)
