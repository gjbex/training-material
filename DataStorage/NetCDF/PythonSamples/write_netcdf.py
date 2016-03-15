#!/usr/bin/env python

from argparse import ArgumentParser
from math import exp
import numpy as np
from netCDF4 import Dataset

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='create NetCDF file')
    arg_parser.add_argument('file', help='file name to use')
    arg_parser.add_argument('-x', type=int, default=10,
                            help='number of x-point')
    arg_parser.add_argument('-y', type=int, default=10,
                            help='number of y-point')
    arg_parser.add_argument('-z', type=int, default=10,
                            help='number of z-point')
    arg_parser.add_argument('-v', dest='version', choices=['3', '4'],
                            default='3', help='NetCDF version to create')
    options = arg_parser.parse_args()
    if options.version == '3':
        version = 'NETCDF3_CLASSIC'
    else:
        version = 'NETCDF4'
    rootgrp = Dataset(options.file, 'w', format='NETCDF3_CLASSIC')
    x_dim = rootgrp.createDimension('x', options.x)
    y_dim = rootgrp.createDimension('y', options.y)
    z_dim = rootgrp.createDimension('z', options.z)
    x_grid = rootgrp.createVariable('x', 'f4', ('x', ))
    y_grid = rootgrp.createVariable('y', 'f4', ('y', ))
    z_grid = rootgrp.createVariable('z', 'f4', ('z', ))
    field = rootgrp.createVariable('field', 'f4', ('x', 'y', 'z'))
    x_grid[:] = np.linspace(0.0, 1.0, num=options.x, endpoint=True)
    y_grid[:] = np.linspace(0.0, 1.0, num=options.y, endpoint=True)
    z_grid[:] = np.linspace(0.0, 1.0, num=options.z, endpoint=True)
    for i, x in enumerate(x_grid):
        for j, y in enumerate(y_grid):
            for k, z in enumerate(z_grid):
                field[i, j, k] = exp(-(x**2 + y**2 + z**2))
    rootgrp.close()
    
