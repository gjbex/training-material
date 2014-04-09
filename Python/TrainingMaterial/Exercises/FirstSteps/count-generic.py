#!/usr/bin/env python

import sys

file_name = sys.argv[1]
nucleotides = 'ACGT'
count = {}
for nucl in nucleotides:
    count[nucl] = 0
with open(file_name, 'r') as input:
    for line in input:
        for nucl in line:
            if nucl in nucleotides:
                count[nucl] += 1
    for nucl in nucleotides:
        print nucl, ': ', count[nucl]

