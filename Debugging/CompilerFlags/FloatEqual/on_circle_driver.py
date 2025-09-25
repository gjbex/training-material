#!/usr/bin/env python3

from math import sqrt
from subprocess import check_output

def compute_y(x, radius):
    return sqrt(radius**2 - x**2)

cases = [
    [0.0, 0.0,  2.0,  2.0,       0.0],
    [0.0, 0.0,  2.0,  0.0,       2.0],
    [0.0, 0.0,  2.0,  sqrt(2.0), sqrt(2.0)],
    [0.0, 0.0,  2.0,  1.0,       compute_y(1.0, 2.0)],
]

cmd = './on_circle_c.exe'
for case in cases:
    args = ['{0:.15f}'.format(x) for x in case]
    print(cmd, ' '.join(args))
    output = check_output([cmd, *args])
    print(output.decode('utf-8').rstrip())
