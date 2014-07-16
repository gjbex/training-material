#!/usr/bin/env python

import random, sys
import numpy, tables

from particle import Particle

def create_data_file(name):
    h5file = tables.openFile(name, mode='a')
    final_state = h5file.createTable(h5file.root.particles, 'final',
                                     Particle, 'final state of particles')
    initial_state = h5file.root.particles.initial
    particle = final_state.row
    for init_particle in initial_state:
        particle['particle_id'] = init_particle['particle_id']
        particle['mass'] = init_particle['mass']
        particle['x_pos'] = random.gauss(0.0, 1.0)
        particle['y_pos'] = random.gauss(0.0, 1.0)
        particle['x_vel'] = random.gauss(0.0, 1.0)
        particle['y_vel'] = random.gauss(0.0, 1.0)
        particle.append()
    h5file.flush()
    return h5file

def main():
    h5file = create_data_file('test.h5')
    print h5file
    h5file.close()
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)


