#!/usr/bin/env python

import sys


def main():
    for line in sys.stdin:
        if line.startswith('end'):
            _, time_str = (x.strip() for x in line.strip().split(':', 1))
            print(time_str)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
