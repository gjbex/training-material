#!/usr/bin/env python

from collections import namedtuple
from math import sqrt
import sys

Result = namedtuple('Result', ['mean', 'stddev'])


def stats():
    sum = 0.0
    sum2 = 0.0
    count = 0
    while True:
        number = yield
        if number is None:
            break
        sum += number
        sum2 += number**2
        count += 1
    return Result(sum/count, sqrt((sum2 - sum**2/count)/(count - 1)))


def process_line(line, mode=float):
    line = line.strip()
    if not line:
        return None
    items = [item.strip() for item in line.split(',')]
    if mode == float:
        return [float(item) for item in items]
    else:
        return items

if __name__ == '__main__':
    line = sys.stdin.readline()
    names = process_line(line, mode='text')
    averagers = [stats() for name in names]
    for averager in averagers:
        next(averager)
    for line in sys.stdin:
        data = process_line(line)
        if not data:
            continue
        for number, averager in zip(data, averagers):
            averager.send(number)
    for name, averager in zip(names, averagers):
        try:
            averager.send(None)
        except StopIteration as exception:
            result = exception.value
            print('{0}: {1:.3f}, {2:.3f}'.format(name,
                                                 result.mean,
                                                 result.stddev))
