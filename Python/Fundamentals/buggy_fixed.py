#!/usr/bin/env python

import sys


def main():
    n = int(sys.argv[1])
    matrix = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            matrix[i][j] = i*n + j + 1
    print('\n'.join([' '.join(['{:2d}'.format(e)
                    for e in row]) for row in matrix]))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
