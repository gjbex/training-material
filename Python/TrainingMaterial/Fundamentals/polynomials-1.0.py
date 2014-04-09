#!/usr/bin/env python

def create_polynom(*coeffs):
    local_coeffs = coeffs
    def polynom(x):
        value = 0.0
        for degree, coeff in enumerate(local_coeffs):
            value += coeff*x**degree
        return value
    return polynom

if __name__ == '__main__':
    second_order = create_polynom(1.0, -3.0, 2.0)
    for i in xrange(-10, 11):
        x = i/10.0
        print '{0:4.1f}\t{1:10.7f}'.format(x, second_order(x))
            
