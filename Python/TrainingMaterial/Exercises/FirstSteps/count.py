#!/usr/bin/env python

import sys

nr_A = 0
nr_C = 0
nr_G = 0
nr_T = 0
for line in sys.stdin:
    for nucl in line:
        if nucl == 'A':
            nr_A += 1
        elif nucl == 'C':
            nr_C += 1
        elif nucl == 'G':
            nr_G += 1
        elif nucl == 'T':
            nr_T += 1
print 'A: ', nr_A
print 'C: ', nr_C
print 'G: ', nr_G
print 'T: ', nr_T
