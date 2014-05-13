#!/usr/bin/env python

class NegArgError(Exception):
    def __init__(self, name, n):
        super(NegArgError, self).__init__()
        self.message = 'argument {0} for {1} negative'.format(n, name)
        
class TooLargeArgError(Exception):
    def __init__(self, name, n):
        super(TooLargeArgError, self).__init__()
        self.message = 'argument {0} for {1} too large'.format(n, name)
        
def check_min(f):
    def wrapped(n):
        if n < 0:
            raise NegArgError(f.func_name, n)
        return f(n)
    wrapped.func_name = f.func_name
    return wrapped
      
def check_max(f):
    def wrapped(n):
        if n > 12:
            raise TooLargeArgError(f.func_name, n)
        return f(n)
    wrapped.func_name = f.func_name
    return wrapped
      
@check_max
@check_min
def fact(n):
    if n == 0:
        return 1
    else:
        return n*fact(n - 1)

if __name__ == '__main__':

    import sys

    for n in [3, 7, 22, -1]:
        try:
            print '{0}! = {1}'.format(n, fact(n))
        except Exception as error:
            sys.stderr.write('### error: {0}\n'.format( error.message))

