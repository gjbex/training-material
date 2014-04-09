class Shape(object):

    def __init__(self, name):
        self._name = name

    @property
    def name(self):
        return self._name

    def __str__(self):
        return self.name
