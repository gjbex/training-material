#!/usr/bin/env python

class Polynomial(object):

    def __init__(self, *coeffs):
        self._coeffs = coeffs

    def __call__(self, x):
        value = 0.0
        for degree, coeff in enumerate(self._coeffs):
            value += coeff*x**degree
        return value

if __name__ == '__main__':
    second_order = Polynomial(1.0, -3.0, 2.0)
    for i in xrange(-10, 11):
        x = i/10.0
        print '{0:4.1f}\t{1:10.7f}'.format(x, second_order(x))
            

