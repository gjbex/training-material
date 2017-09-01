#!/usr/bin/env python

# place definition in global scope
with open('fib.py', 'r') as func_file:
    func_str = ''.join(func_file.readlines())
exec(func_str)
n = 5
print('fib({0:d}) = {1:d}'.format(n, fib(n)))

# place definitions in private scope, no problem for non-recursive functions
with open('fac_iter.py', 'r') as func_file:
    func_str = ''.join(func_file.readlines())
priv_globals = {}
priv_locals = {}
exec(func_str, priv_globals, priv_locals)
print('fac({0:d}) = {1:d}'.format(n, priv_locals['fac_iter'](n)))

# place definitions in private scope, problem for recursive functions
with open('fac.py', 'r') as func_file:
    func_str = ''.join(func_file.readlines())
priv_globals = {}
priv_locals = {}
exec(func_str, priv_globals, priv_locals)
try:
    result = eval('fac({0})'.format(n), priv_globals, priv_locals)
    print('fac({0:d}) = {1:d}'.format(n, result))
except NameError as error:
    print('Exception: {0}'.format(str(error)))

# when evaluating within string, no problem
exec('{0}\nresult = fac({1:d})'.format(func_str, 5))
print('fac({0:d}) = {1:d}'.format(n, result))
