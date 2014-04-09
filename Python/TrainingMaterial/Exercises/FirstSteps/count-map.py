#!/usr/bin/env python

import sys

count = {
    'A': 0,
    'C': 0,
    'G': 0,
    'T': 0,
}
for line in sys.stdin:
    for nucl in line:
        if nucl in 'ACGT':
            count[nucl] += 1
for nucl in 'ACGT':
    print nucl, ': ', count[nucl]

