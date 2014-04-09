#!/usr/bin/env python

from math import sqrt
import sys

def main():
    names_str = sys.stdin.readline().rstrip()
    names = [x.strip() for x in names_str.split(',')]
    sums = [0.0] * len(names)
    sums2 = [0.0] * len(names)
    nr_cols = 0
    for line in sys.stdin.readlines():
        if len(line.strip()) > 0:
            data = [float(x) for x in line.rstrip().split(',')]
            sums = [x + y for x, y in zip(sums, data)]
            sums2 = [x + y**2 for x, y in zip(sums2, data)]
            nr_cols += 1
    if nr_cols > 0:
        for name, s, s2 in zip(names, sums, sums2):
            mean = s/nr_cols
            stddev = sqrt((s2 - nr_cols*mean**2)/nr_cols)
            print '{0}: {1:.2f}, {2:.2f}'.format(name, mean, stddev)
        return 0
    else:
        sys.stderr.write('no data given')
        return 1

if __name__ == '__main__':
    status = main()
    sys.exit(status)

