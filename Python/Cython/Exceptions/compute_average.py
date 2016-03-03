#!/usr/bin/env python

from argparse import ArgumentParser
import array
import average


size = 10

arg_parser = ArgumentParser(description='test Cython errors')
arg_parser.add_argument('--m', type=int, default=0, help='lower bound')
arg_parser.add_argument('--n', type=int, default=size, help='upper bound')
options = arg_parser.parse_args()
data = array.array('d', list(range(size)))
print('with except:')
try:
    print(average.average(data, options.m, options.n))
except Exception as e:
    print('caught exception {0}: {1}'.format(str(e.__class__), str(e)))
print('without except:')
try:
    print(average.average_no_except(data, options.m, options.n))
    print('no exception caught')
except Exception as e:
    print('caught exception {0}: {1}'.format(e.__class__, str(e)))
