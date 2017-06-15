#!/usr/bin/env python
'''Test to see whether class variables and methods are in fact
inherited.'''

class Parent(object):
    '''Parent class'''

    __class_var = 10

    @classmethod
    def get_class_var(cls):
        return cls.__class_var

    @classmethod
    def set_class_var(cls, value):
        cls.__class_var = value

    def __init__(self, obj_var):
        self.__obj_var = obj_var

    @property
    def obj_var(self):
        return self.__obj_var

    @obj_var.setter
    def obj_var(self, value):
        self.__obj_var = value

    def __str__(self):
        return str(self.obj_var)


class Child(Parent):
    '''Child class'''

    def __init__(self, obj_var, new_ojb_var):
        super().__init__(obj_var)
        self.__new_obj_var = new_ojb_var

    @property
    def child_var(self):
        return self.__new_obj_var

    def __str__(self):
        return super().__str__() + ' ' + str(self.child_var)


if __name__ == '__main__':
    p = Parent('abc')
    c = Child('bde', 'efg')
    print('Parent: {}'.format(Parent.get_class_var()))
    print('Child: {}'.format(Child.get_class_var()))
    print('setting Child class variable')
    Child.set_class_var(15)
    print('Parent: {}'.format(Parent.get_class_var()))
    print('Child: {}'.format(Child.get_class_var()))
    print('setting Parent class variable')
    Parent.set_class_var(25)
    print('Parent: {}'.format(Parent.get_class_var()))
    print('Child: {}'.format(Child.get_class_var()))
