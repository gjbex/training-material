#!/usr/bin/env python

import sys
from log_map import logistic_map


def main():
    for i in range(0, 11):
        x = float(i)/10.0
        y = logistic_map(x, 3.2, 1000)
        print(x, y)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
