#!/usr/bin/env python

if __name__ == '__main__':
    
    from argparse import ArgumentParser
    from math import exp
    import numpy as np

    min_val = -1.0
    max_val = 1.0
    default_points = 10
    default_a = 1.0
    arg_parser = ArgumentParser(description='produce a 3D scalar field')
    arg_parser.add_argument('-x', type=int, default=default_points,
                            help='number of x points')
    arg_parser.add_argument('-y', type=int, default=default_points,
                            help='number of y points')
    arg_parser.add_argument('-z', type=int, default=default_points,
                            help='number of z points')
    arg_parser.add_argument('-a_x', type=float, default=default_a,
                            help='alpha_x')
    arg_parser.add_argument('-a_y', type=float, default=default_a,
                            help='alpha_y')
    arg_parser.add_argument('-a_z', type=float, default=default_a,
                            help='alpha_z')
    options = arg_parser.parse_args()
    print 'x,y,z,value'
    for x in np.linspace(min_val, max_val, num=options.x, endpoint=True):
        for y in np.linspace(min_val, max_val, num=options.y, endpoint=True):
            for z in np.linspace(min_val, max_val, num=options.z, endpoint=True):
                val = exp(-(options.a_x*x**2 +
                            options.a_y*y**2 +
                            options.a_z*z**2))
                print '{x:.4f},{y:.4f},{z:.4f},{val:.8f}'.format(x=x,
                                                                 y=y,
                                                                 z=z,
                                                                 val=val)

