#!/usr/bin/env python

import numpy as np
import tables

def compute_centers(h5file, nr_centers=5, avg_dist=100.0):
    '''compute positions of nr_centers of gravity, at an average
       distance avg_dist from the origin'''
    centers = avg_dist*np.random.randn(nr_centers, 3)    
    h5file.create_array(h5file.root, 'centers', centers,
                        'center points for distributions')
    return centers

def compute_particles(hrfile, center, nr_particles=10, avg_dist=10.0,
                      avg_radial_vel=1.0, avg_rand_vel=0.1,
                      min_mass=0.01, max_mass=10.0):
    '''compute nr_particles around the given center of gravity,
       with average distane avg_dist and average velocity avg_vel'''
    particles = h5file.createGroup(h5file.root, 'particles')
    position = h5file.create_earray(particles, 'position', tables.Float64Atom(),
                                    (0, 3), 'particle positions')
    velocity = h5file.create_earray(particles, 'velocity', tables.Float64Atom(),
                                    (0, 3), 'particle velocities')
    mass = h5file.create_earray(particles, 'mass', tables.Float64Atom(),
                                    (0,), 'particle masses')
    for center in centers:
        pos = avg_dist*(center + np.random.randn(nr_particles, 3))
        position.append(pos)
        vel = (avg_rand_vel*np.random.randn(nr_particles, 3) +
               avg_radial_vel*(pos - center))
        velocity.append(vel)
        mass.append(np.random.uniform(min_mass, max_mass, nr_particles))
    h5file.flush()


def compute_grid(h5file, group='grid', extent=750.0, points=1000):
    '''compute grid for scalar and vector field data'''
    x = np.linspace(-extent, extent, points, endpoint=True)
    y = np.linspace(-extent, extent, points, endpoint=True)
    z = np.linspace(-extent, extent, points, endpoint=True)
    grid = h5file.createGroup(h5file.root, group, 'grid coordinates')
    h5file.create_array(grid, 'x', x, 'x coordinates')
    h5file.create_array(grid, 'y', y, 'y coordinates')
    h5file.create_array(grid, 'z', z, 'z coordinates')
    h5file.flush()
    return x, y, z

def compute_scalar_field(h5file, centers, xs, ys, zs, max_field=5000.0, array='scalar'):
    '''compute scalar field, that decreases quadratically with the distance to
       the center'''
    field = h5file.create_earray(h5file.root, array, tables.Float64Atom(),
                         (len(xs), len(ys), 0), 'scalar field data')
    for z in zs:
        X, Y, Z = np.meshgrid(xs, ys, np.array(z))
        field_slice = np.zeros((len(xs), len(ys), 1))
        for center in centers:
            field_slice += max_field/np.sqrt((X - center[0])**2 + (Y - center[1])**2 +
                                             (Z - center[2])**2 + 1.0)
        field.append(field_slice)
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
    centers = compute_centers(h5file, options.centers, options.avg_center_dist)
    if options.verbose:
        print 'center positions'
        print centers
    if options.particle_data:
        compute_particles(h5file, centers, options.particles,
                          options.avg_part_radial_vel, options.avg_part_random_vel)
    x, y, z = compute_grid(h5file, extent=options.extent, points=options.points)
    if options.verbose:
        print 'grid x'
        print x
        print 'grid y'
        print y
        print 'grid z'
        print z
    if options.scalar_field_data:
        compute_scalar_field(h5file, centers, x, y, z, options.max_temp)
    h5file.close()

