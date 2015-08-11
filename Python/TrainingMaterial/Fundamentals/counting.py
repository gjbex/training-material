#!/usr/bin/env python

import sys
import data_parsing


def main():
    sys.stdin.readline()
    threshold = 1.0e-7
    counter = {'negative': 0, 'zero': 0, 'positive': 0}
    for line in sys.stdin:
        (_, _, value) = data_parsing.parse_line(line)
        if value < -threshold:
            counter['negative'] += 1
        elif value > threshold:
            counter['positive'] += 1
        else:
            counter['zero'] += 1
    for key, value in counter.items():
        print('{0}: {1}'.format(key, value))

if __name__ == '__main__':
    main()
