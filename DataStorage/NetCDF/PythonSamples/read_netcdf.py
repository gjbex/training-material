#!/usr/bin/env python

from math import exp, fabs
from argparse import ArgumentParser
from netCDF4 import Dataset

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='verify NetCDF file')
    arg_parser.add_argument('file', help='file to verify')
    options = arg_parser.parse_args()
    rootgrp = Dataset(options.file)
    x_grid = rootgrp.variables['x']
    y_grid = rootgrp.variables['y']
    z_grid = rootgrp.variables['z']
    field = rootgrp.variables['field']
    max_diff = 0.0
    for i, x in enumerate(x_grid):
        for j, y in enumerate(y_grid):
            for k, z in enumerate(z_grid):
                diff = fabs(field[i, j, k] - exp(-(x**2 + y**2 + z**2)))
                if diff > max_diff:
                    max_diff = diff
    print('maximum difference = {0:.4e}'.format(max_diff))
