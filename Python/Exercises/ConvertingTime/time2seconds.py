#!/usr/bin/env python

import sys

def main():
    units = [1, 60, 3600]
    parts = [int(x) for x in sys.argv[1].split(':')]
    parts.reverse()
    result = sum([x*y for x, y in zip(parts, units)])
    print result
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

