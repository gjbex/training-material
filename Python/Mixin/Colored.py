class Colored(object):

    @property
    def color(self):
        return self._color

    @color.setter
    def color(self, value):
        self._color = value
