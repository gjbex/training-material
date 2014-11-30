#!/usr/bin/env python

import numpy as np
import tables

from particle import Particle
from grid import Grid
from scalar_field import ScalarField

def compute_centers(nr_centers=5, avg_dist=100.0):
    '''compute positions of nr_centers of gravity, at an average
       distance avg_dist from the origin'''
    return avg_dist*np.random.randn(nr_centers, 3)    

def compute_particles(center, nr_particles=10, avg_dist=10.0,
                      avg_radial_vel=1.0, avg_rand_vel=0.1,
                      min_mass=0.01, max_mass=10.0):
    '''compute nr_particles around the given center of gravity,
       with average distane avg_dist and average velocity avg_vel'''
    part_pos = None
    part_vel = None
    for center in centers:
        pos = avg_dist*(center + np.random.randn(nr_particles, 3))
        vel = (avg_rand_vel*np.random.randn(nr_particles, 3) +
               avg_radial_vel*(pos - center))
        if part_pos is None:
            part_pos = pos
        else:
            part_pos = np.vstack((part_pos, pos))
        if part_vel is None:
            part_vel = vel
        else:
            part_vel = np.vstack((part_vel, vel))
    mass = np.random.uniform(min_mass, max_mass, len(part_pos))
    return part_pos, part_vel, mass

def store_particles(h5file, pos, vel, mass, table='particles'):
    '''sotre particle data in HDF5 file'''
    particles = h5file.createTable(h5file.root, table, Particle,
                                   'particle data')
    particle = particles.row
    for i in xrange(len(pos)):
        particle['x_pos'] = pos[i, 0]
        particle['y_pos'] = pos[i, 1]
        particle['z_pos'] = pos[i, 2]
        particle['x_vel'] = vel[i, 0]
        particle['y_vel'] = vel[i, 1]
        particle['z_vel'] = vel[i, 2]
        particle['mass'] = mass[i]
        particle.append()
    h5file.flush()

def compute_grid(extent=750.0, points=1000):
    '''compute grid for scalar and vector field data'''
    x = np.linspace(-extent, extent, points + 1, endpoint=True)
    y = np.linspace(-extent, extent, points + 2, endpoint=True)
    z = np.linspace(-extent, extent, points + 3, endpoint=True)
    return x, y, z

def store_grid(h5file, x, y, z, group='grid'):
    '''store grid coordinates in HDF5 file's group'''
    grid = h5file.createGroup(h5file.root, group, 'grid coordinates')
    h5file.create_array(grid, 'x', x, 'x coordinates')
    h5file.create_array(grid, 'y', y, 'y coordinates')
    h5file.create_array(grid, 'z', z, 'z coordinates')
    h5file.flush()

def compute_scalar_field(centers, xs, ys, zs, max_temp=5000.0):
    '''compute the temperature field, that decreases quadratically
       with the distance to the center'''
    field_func = lambda x, y: max_temp/sum((x- y)**2)
    field = np.zeros((len(xs), len(ys), len(zs)))
    for i, x in enumerate(xs):
        for j, y in enumerate(ys):
            for k, z in enumerate(zs):
                for center in centers:
                    field[i, j, k] = field_func(np.array([x, y, z]), center)
    return field

def store_scalar_field(h5file, field, array='scalar'):
    '''store scalar field values in HDF5 file'''
    h5file.create_array(h5file.root, array, field, 'scalar field data')
    h5file.flush()

if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    arg_parser = ArgumentParser(description='data generator')
    arg_parser.add_argument('--centers', type=int, default=5,
                            help='number of centers')
    arg_parser.add_argument('--particle-data', action='store_true',
                            help='generate particle data')
    arg_parser.add_argument('--avg-center-dist', type=float, default=100.0,
                            help='average distance between centers')
    arg_parser.add_argument('--particles', type=int, default=10,
                            help='number of particles/center')
    arg_parser.add_argument('--avg-part-dist', type=float, default=5.0,
                            help='average distance between particles')
    arg_parser.add_argument('--avg-part-radial-vel', type=float,
                            default=1.0,
                            help='average radial velocity of particles')
    arg_parser.add_argument('--avg-part-random-vel', type=float,
                            default=0.1,
                            help='average random velocity of particles')
    arg_parser.add_argument('--scalar-field-data', action='store_true',
                            help='generate scalar field data')
    arg_parser.add_argument('--points', type=int, default=1000,
                            help='number of points in each dimension')
    arg_parser.add_argument('--extent', type=float, default=750.0,
                            help='maxumum grid coordinate')
    arg_parser.add_argument('--max_temp', type=float, default=5000.0,
                            help='maximum temperature')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='verbose output for debugging')
    arg_parser.add_argument('file', help='HDF5 file to store the data in')
    options = arg_parser.parse_args()
    h5file = tables.openFile(options.file, mode='w', title='synthetic data set')
    centers = compute_centers(options.centers, options.avg_center_dist)
    if options.verbose:
        print 'center positions'
        print centers
    if options.particle_data:
        part_pos, part_vel, part_mass = compute_particles(centers,
                                                          options.particles,
                                                          options.avg_part_radial_vel,
                                                          options.avg_part_random_vel)
        if options.verbose:
            print 'particle positions'
            print part_pos
            print 'particle velocities'
            print part_vel
        store_particles(h5file, part_pos, part_vel, part_mass)
    x, y, z = compute_grid(options.extent, options.points)
    store_grid(h5file, x, y, z)
    if options.verbose:
        print 'grid x'
        print x
        print 'grid y'
        print y
        print 'grid z'
        print z
    if options.scalar_field_data:
        field = compute_scalar_field(centers, x, y, z, options.max_temp)
        if options.verbose:
            print 'scalar field'
            print field
        store_scalar_field(h5file, field)
    h5file.close()

