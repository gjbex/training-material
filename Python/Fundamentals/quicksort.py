#!/usr/bin/env python

import sys


def partition(data, low, high):
    pivot = data[high]
    lower_idx = low - 1
    for i in range(low, high):
        if data[i] < pivot:
            lower_idx += 1
            data[lower_idx], data[i] = data[i], data[lower_idx]
    lower_idx += 1
    data[lower_idx], data[high] = data[high], data[lower_idx]
    return lower_idx


def qsort(data, low=None, high=None):
    if low is None:
        low, high = 0, len(data) - 1
    if low < high:
        pivot = partition(data, low, high)
        qsort(data, low, pivot - 1)
        qsort(data, pivot + 1, high)


if __name__ == '__main__':
    data = list(map(float, sys.argv[1:]))
    qsort(data)
    print(' '.join(map(str, data)))
