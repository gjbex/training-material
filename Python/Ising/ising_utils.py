#!/usr/bin/env python

def print_ising(ising, file):
    for i in xrange(ising.N):
        for j in xrange(ising.N):
            file.write('{0:3d}'.format(ising.s(i, j)))
        file.write('\n')

