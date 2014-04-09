#!/usr/bin/env python

import random, sys
import tables

from particle import Particle

def create_data_file(name):
    h5file = tables.openFile(name, mode='w', title='Model properties')
    particle_group = h5file.createGroup(h5file.root, 'particles',
                                        "system's particles' state")
    initial_state = h5file.createTable(particle_group, 'initial', Particle,
                                       'initial state of particles')
    particle = initial_state.row
    for particle_id in xrange(100):
        particle['particle_id'] = particle_id
        particle['mass'] = random.gauss(0.0, 1.0)
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


