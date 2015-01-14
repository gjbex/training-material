#!/usr/bin/env python

import sys

def main():
    total_seconds = int(sys.argv[1])
    units = [3600, 60, 1]
    parts = [0] * 3
    idx = 0
    while total_seconds > 0:
        parts[idx] = total_seconds/units[idx]
        total_seconds = total_seconds % units[idx]
        idx += 1
    print ':'.join('{:02d}'.format(x) for x in parts)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

