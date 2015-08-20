#!/usr/bin/env python

import random
import sys

if __name__ == '__main__':
    digits = list(range(2, 10))
    for _ in range(500):
        for _ in range(6):
            sys.stdout.write(str(random.choice(digits)))
        sys.stdout.write('\n')
