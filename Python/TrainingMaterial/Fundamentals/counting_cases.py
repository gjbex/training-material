#!/usr/bin/env python

import sys


def main():
    sys.stdin.readline()
    counter = {}
    for line in sys.stdin:
        value = int(line.rstrip('\r\n').split()[1])
        if value not in counter:
            counter[value] = 0
        counter[value] += 1
    for value, count in list(counter.items()):
        print('{0}: {1}'.format(value, count))

if __name__ == '__main__':
    main()
