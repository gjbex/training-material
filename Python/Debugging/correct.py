#!/usr/bin/env python

import sys


def create_matrix(n):
    return [[0] * n for _ in range(n)]


def init_matrix(matrix):
    m = len(matrix)
    n = len(matrix[0])
    for i in range(m):
        for j in range(n):
            matrix[i][j] = i*n + j + 1


def print_matrix(matrix):
    fmt_elem = lambda elem: '{:2d}'.format(elem)
    print('\n'.join(' '.join(fmt_elem(e) for e in row) for row in matrix))


def main():
    n = int(sys.argv[1])
    matrix = create_matrix(n)
    init_matrix(matrix)
    print_matrix(matrix)
    return 0


if __name__ == '__main__':
    sys.exit(main())
