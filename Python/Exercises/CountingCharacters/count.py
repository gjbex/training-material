#!/usr/bin/env python

import sys

def main():
    count = {}
    for line in sys.stdin.readlines():
        for c in line.strip():
            if c not in count:
                count[c] = 0
            count[c] += 1
    for c in sorted(count.keys()):
        print '{0}: {1}'.format(c, count[c])
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

