#!/usr/bin/env python

import sys
from comp_pi import compute_pi


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 1000
    print(compute_pi(n))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
