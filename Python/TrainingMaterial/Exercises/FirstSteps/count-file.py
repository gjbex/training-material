#!/usr/bin/env python

import sys

file_name = sys.argv[1]
count = {
    'A': 0,
    'C': 0,
    'G': 0,
    'T': 0,
}
with open(file_name, 'r') as input:
    for line in input:
        for nucl in line:
            if nucl in 'ACGT':
                count[nucl] += 1
    for nucl in 'ACGT':
        print nucl, ': ', count[nucl]

