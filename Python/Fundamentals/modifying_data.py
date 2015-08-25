#!/usr/bin/env python

import sys


def main():
    print(sys.stdin.readline().rstrip('\r\n'))
    for line in sys.stdin:
        data = line.rstrip('\r\n').split()
        if float(data[2]) < 0.0:
            data[2] = 0.0
        print(data[0], data[1], data[2])

if __name__ == '__main__':
    main()
