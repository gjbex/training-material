#!/usr/bin/env python

import sys


def create_matrix(n):
    return [[0] * n for _ in range(n)]


def init_matrix(matrix):
    nr_rows = len(matrix)
    nr_cols = len(matrix[0])
    for i in range(nr_rows):
        for j in range(nr_cols):
            matrix[i][j] = i*nr_cols + j + 1


def sum_matrix(matrix):
    return sum(map(sum, matrix))


def main():
    n = int(sys.argv[1])
    matrix = create_matrix(n)
    init_matrix(matrix)
    print('sum = {0}'.format(sum_matrix(matrix)))

    def fmt_elem(element):
        return '{:2d}'.format(element)

    print('\n'.join(' '.join(fmt_elem(e) for e in row) for row in matrix))
    return 0


if __name__ == '__main__':
    sys.exit(main())
