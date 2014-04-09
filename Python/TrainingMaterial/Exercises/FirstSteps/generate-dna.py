#!/usr/bin/env python

import random, sys

if len(sys.argv) > 1:
    n = int(sys.argv[1])
else:
    n = 10
for _ in xrange(n):
    sys.stdout.write(random.choice('ACGT'))
