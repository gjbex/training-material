#!/usr/bin/env python

from argparse import ArgumentParser
import h5py
import numpy as np
import sys

from figures import (CircleGenerator, SquareGenerator,
                     TriangleGenerator, FigureTransformer)


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='generate data set of '
                                            'random geometrical objects')
    arg_parser.add_argument('--n', type=int, default=1,
                            help='number of objects to create')
    arg_parser.add_argument('--max_objects', type=int, default=1,
                            help='maximum number of objects per '
                                 'image')
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
    arg_parser.add_argument('--blur_factor', type=float, default=3.0,
                            help='maximum blur applied to image')
    arg_parser.add_argument('--label', action='store_true',
                            help='add labeled output')
    arg_parser.add_argument('--seed', type=int,
                            help='seed for random number generator')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='verbose output for debugging')
    arg_parser.add_argument('file', help='HDF5 file with data')
    options = arg_parser.parse_args()
    if options.label and options.max_objects != 1:
        print('### error: labels only make sense for single objects',
              file=sys.stderr)
        sys.exit(10)
    if options.seed is not None:
        np.random.seed(options.seed)
    generators = [
        CircleGenerator(options.width, options.height,
                        options.max_size),
        SquareGenerator(options.width, options.height,
                        options.max_size),
        TriangleGenerator(options.width, options.height,
                          options.max_size),
    ]
    figure_names = ['circle', 'square', 'triangle']
    transformer = FigureTransformer(width=options.width,
                                    height=options.height,
                                    min_size=options.min_size,
                                    max_size=options.max_size,
                                    center_margin=options.center_margin,
                                    blur_factor=options.blur_factor)
    if options.verbose:
        print(f'starting generation of {options.n} images...',
              file=sys.stderr)
    x_data = np.empty((options.n, options.width, options.height),
                      dtype=np.uint8)
    y_data = np.zeros((options.n, len(generators)), dtype=np.uint8)
    labels = list()
    for i in range(options.n):
        data = np.zeros((options.width, options.height))
        nr_objects = np.random.randint(1, options.max_objects + 1)
        for j in range(nr_objects):
            object_id = np.random.randint(0, len(generators))
            fig = generators[object_id].create()
            transformer.transform(fig)
            data += fig.data
            y_data[i, object_id] += 1
            if options.label:
                labels.append(figure_names[object_id].encode('ascii',
                                                             'ignore'))
        x_data[i, :, :] = (255*data/nr_objects).astype(np.uint8)
    if options.verbose:
        print(f"writing to file '{options.file}'", file=sys.stderr)
    with h5py.File(options.file, 'w') as hdf5_file:
        hdf5_file.create_dataset('x_values', data=x_data)
        hdf5_file.create_dataset('y_values', data=y_data)
        if options.label:
            hdf5_file.create_dataset('y_labels', (len(labels), 1), 'S8',
                                     labels)
