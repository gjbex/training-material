#!/usr/bin/env python

from math import sqrt
import sys

def main():
    names_str = sys.stdin.readline().rstrip()
    names = []
    for name in names_str.split(','):
        names.append(name.strip())
    nr_cols = len(names)
    sums = []
    sums2 = []
    for i in xrange(nr_cols):
        sums.append(0.0)
        sums2.append(0.0)
    nr_rows = 0
    for line in sys.stdin.readlines():
        if len(line.strip()) > 0:
            data = line.rstrip().split(',')
            for i in xrange(nr_cols):
                sums[i] += float(data[i])
                sums2[i] += float(data[i])**2
            nr_rows += 1
    if nr_cols > 0:
        for i in xrange(nr_cols):
            mean = sums[i]/nr_rows
            stddev = sqrt((sums2[i] - nr_rows*mean**2)/nr_rows)
            print '{0}: {1:.2f}, {2:.2f}'.format(names[i], mean, stddev)
        return 0
    else:
        sys.stderr.write('no data given')
        return 1

if __name__ == '__main__':
    status = main()
    sys.exit(status)

