#!/usr/bin/env python

from math import sqrt
import sys
import tables

def main():
    h5file = tables.openFile('test.h5', mode='r')
    initial = h5file.root.particles.initial
    high_energy = [(x['particle_id'], x['x_vel'], x['y_vel'])
                      for x in initial
                          if sqrt(x['x_vel']**2 + x['y_vel']**2) > 3.0]
    print ', '.join([str(x[0]) for x in high_energy])
    for data in high_energy:
        print data
    h5file.close()
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

