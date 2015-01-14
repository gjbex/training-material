#!/usr/bin/env python

import random, sys

if __name__ == '__main__':
    digits = range(2, 10)
    for _ in xrange(500):
        for _ in xrange(6):
            sys.stdout.write(str(random.choice(digits)))
        sys.stdout.write('\n')

