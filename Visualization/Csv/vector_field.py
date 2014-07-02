#!/usr/bin/env python

if __name__ == '__main__':
    
    from argparse import ArgumentParser
    from math import exp, sqrt, sin, cos, atan, pi
    import numpy as np

    min_val = -1.0
    max_val = 1.0
    default_points = 10
    arg_parser = ArgumentParser(description='produce a 3D scalar field')
    arg_parser.add_argument('-x', type=int, default=default_points,
                            help='number of x points')
    arg_parser.add_argument('-y', type=int, default=default_points,
                            help='number of y points')
    arg_parser.add_argument('-z', type=int, default=default_points,
                            help='number of z points')
    options = arg_parser.parse_args()
    fmt_str = '{x:.4f},{y:.4f},{z:.4f},{v_x:.8f},{v_y:.8f},{v_z:.8f}'
    print 'x,y,z,v_x,v_y,v_z'
    for z in np.linspace(0.0, max_val, num=options.z, endpoint=True):
        for x in np.linspace(min_val, max_val, num=options.x, endpoint=True):
            for y in np.linspace(min_val, max_val, num=options.y, endpoint=True):
                d = sqrt(x**2 + y**2 + z**2)
                v = (1.0 - exp(-d))*exp(-d)
                theta = atan(y/x)
                if x < 0.0:
                    theta += pi
                v_x = v*sin(-theta)
                v_y = v*cos(theta)
                v_z = 0.1*exp(-3.0*z)
                print fmt_str.format(x=x, y=y, z=z,
                                     v_x=v_x, v_y=v_y,v_z=v_z)

