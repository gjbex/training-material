#!/usr/bin/env python

import sys


def main():
    sys.stdin.readline()
    threshold = 1.0e-7
    categories = {
        'negative': lambda x: x < -threshold,
        'zero': lambda x: -threshold <= x <= threshold,
        'positive': lambda x: threshold < x,
    }
    counter = {name: 0 for name in categories}
    for line in sys.stdin:
        value = float(line.rstrip('\r\n').split()[2])
        for name, cond in categories.items():
            if cond(value):
                counter[name] += 1
                break
    for name, value in counter.items():
        print('{0}: {1}'.format(name, value))

if __name__ == '__main__':
    main()
