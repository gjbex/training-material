#!/usr/bin/env python

import sys
import stats


def main():
    n = 100
    data = stats.floatArray(n)
    for i in range(n):
        data[i] = float(i + 1)
    data_stats = stats.stats(data, n)
    print('mean: {0:.2f}, stddev: {1:.2f}'.format(data_stats.mean,
                                                  data_stats.stddev))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
