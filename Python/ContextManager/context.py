#!/usr/bin/env python

from contextlib import contextmanager
import sys


class ContextTest(object):

    def __init__(self, context_nr):
        self._context_nr = context_nr
        print('created with {0}'.format(self._context_nr))

    def __enter__(self):
        print('entering {0}'.format(self._context_nr))
        return self

    def __exit__(self, exception_type, exception_value, backtrace):
        print('exiting {0}'.format(self._context_nr))
        if exception_type:
            print('exception in context {0}:'.format(self._context_nr))
            print('\t', exception_type, exception_value, backtrace)
            return
        else:
            print('no exception in context {0}'.format(self._context_nr))


@contextmanager
def label(name):
    print('entering label({0})'.format(name))
    yield name
    print('exiting label({0})'. format(name))


def main():
    with ContextTest(1) as c1, ContextTest(2) as c2:
        print('in context {0}'.format(c1._context_nr))
        print('in context {0}'.format(c2._context_nr))
    with label('foo') as foo, label('bar') as bar:
        print(foo, bar)
    with ContextTest(1) as c1, ContextTest(2) as c2:
        print('in context {0}'.format(c1._context_nr))
        raise Exception()
        print('in context {0}'.format(c2._context_nr))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
