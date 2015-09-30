#!/usr/bin/env python

from operator import itemgetter

data = [
    ('c', (19, 1)),
    ('b', (12, 2)),
    ('d', (13, 4)),
    ('a', (17, 3)),
]


def print_data(msg, data):
    print(msg)
    data_str = '\t' + '\n\t'.join([str(x) for x in data])
    print(data_str)

if __name__ == '__main__':
    print_data('original list', data)
    sorted_data = sorted(data, key=lambda x: x[1][0])
    print_data('lambda sort', sorted_data)
    sorted_data = sorted(data, key=itemgetter(1, 0))
    print_data('itemgetter sort', sorted_data)
