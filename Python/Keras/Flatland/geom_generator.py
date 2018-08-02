#!/usr/bin/env python

from argparse import ArgumentParser
import h5py
import numpy as np
import random

from figures import (CircleGenerator, SquareGenerator,
                     TriangleGenerator, FigureTransformer)


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='generate data set of '
                                            'random geometrical objects')
    arg_parser.add_argument('--n', type=int, default=1,
                            help='number of objects to create')
    arg_parser.add_argument('--width', type=int, default=100,
                            help='width of the images to create')
    arg_parser.add_argument('--height', type=int, default=100,
                            help='height of the images to create')
    arg_parser.add_argument('--min_size', type=int, default=10,
                            help='minimum size of the oobjects')
    arg_parser.add_argument('--max_size', type=int, default=25,
                            help='maximum size of the objects')
    arg_parser.add_argument('--center_margin', type=float, default=0.3,
                            help='fraction of image width that can '
                                  'not contain the center of an '
                                  'object')
    arg_parser.add_argument('file', help='HDF5 file with data')
    arg_parser.add_argument('--blur_factor', type=float, default=3.0,
                            help='maximum blur applied to image')
    options = arg_parser.parse_args()
    generators = [
        CircleGenerator(options.width, options.height,
                        options.max_size),
        SquareGenerator(options.width, options.height,
                        options.max_size),
        TriangleGenerator(options.width, options.height,
                          options.max_size),
    ]
    transformer = FigureTransformer(width=options.width,
                                    height=options.height,
                                    min_size=options.min_size,
                                    max_size=options.max_size,
                                    center_margin=options.center_margin,
                                    blur_factor=options.blur_factor)
    x_data = np.empty((options.n, options.width, options.height),
                      dtype=np.uint8)
    y_data = np.empty(options.n, dtype=np.uint8)
    for i in range(options.n):
        object_id = random.randint(0, len(generators) - 1)
        fig = generators[object_id].create()
        transformer.transform(fig)
        x_data[i, :, :] = (255*fig.data).astype(np.uint8)
        y_data[i] = object_id
    with h5py.File(options.file, 'w') as hdf5_file:
        hdf5_file.create_dataset('x_values', data=x_data)
        hdf5_file.create_dataset('y_values', data=y_data)
