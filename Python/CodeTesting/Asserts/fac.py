#!/usr/bin/env python

def fac(n):
    '''compute the factorial of given number'''
    assert type(n) == int, 'argument must be integer'
    assert n >= 0, 'argument must be positive'
    if n > 1:
        return n*fac(n - 1)
    else:
        return 1

if __name__ == '__main__':
    for i in range(5):
        print('{0}! = {1}'.format(i, fac(i)))
    for i in [-2, 0.3, 3.0]:
        try:
            print('{0}! = {1}'.format(i, fac(i)))
        except AssertionError as error:
            print('{0}! failed: "{1}"'.format(i, error))
