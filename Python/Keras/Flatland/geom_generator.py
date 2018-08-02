#!/usr/bin/env python

from argparse import ArgumentParser
import h5py
import numpy as np
import random
from scipy.ndimage import filters, interpolation


class Figure:

    def __init__(self, data, x, y, size):
        self.x = x
        self.y = y
        self.size = size
        self.data = data.copy()


class FigureTransformer:

    def __init__(self, width, height, min_size, max_size,
                 center_margin, blur_factor):
        self.height = height
        self.width = width
        self.min_size = min_size
        self.max_size = max_size
        self.center_margin = center_margin
        self.x_low = -0.5*self.width*(1.0 - self.center_margin)
        self.x_high = 0.5*self.width*(1.0 - self.center_margin)
        self.y_low = -0.5*self.height*(1.0 - self.center_margin)
        self.y_high = 0.5*self.height*(1.0 - self.center_margin)
        self.blur_factor = blur_factor

    def scale(self, fig, scale=None):
        if scale is None:
            scale = np.random.uniform(low=self.min_size/self.max_size,
                                      high=1.0)
        matrix = np.array([[1.0/scale, 0.0], [0.0, 1.0/scale]])
        in_center = 0.5*np.array(fig.data.shape)
        offset = in_center - in_center.dot(matrix)
        in_center = 0.5*np.array(fig.data.shape)
        offset = in_center - in_center.dot(matrix)
        fig.data = interpolation.affine_transform(fig.data, matrix,
                                                  offset=offset)
        fig.size *= scale

    def rotate(self, fig, angle=None):
        if angle is None:
            angle = np.random.uniform(low=0.0, high=2.0*np.pi)
        matrix = np.array([
            [np.cos(angle), -np.sin(angle)],
            [np.sin(angle),  np.cos(angle)]])
        in_center = 0.5*np.array(fig.data.shape)
        offset = in_center - in_center.dot(matrix)
        fig.data = interpolation.affine_transform(fig.data, matrix.T,
                                                  offset=offset)

    def shift(self, fig, x=None, y=None):
        if x is None:
            x = np.random.uniform(low=self.x_low, high=self.x_high)
        if y is None:
            y = np.random.uniform(low=self.y_low, high=self.y_high)
        fig.x += x
        fig.y += y
        fig.data = interpolation.shift(fig.data, (x, y))

    def blur(self, fig, blur_factor=None):
        if blur_factor is None:
            blur_factor = np.random.uniform(low=0.5,
                                            high=self.blur_factor)
        fig.data = filters.gaussian_filter(fig.data, blur_factor)

    def transform(self, fig):
        self.scale(fig)
        self.rotate(fig)
        self.shift(fig)
        self.blur(fig)


class FigureGenerator:

    def __init__(self, width, height, max_size):
        self.height = height
        self.width = width
        self.max_size = max_size


class CircleGenerator(FigureGenerator):

    def create(self):
        data = np.zeros((self.width, self.height))
        x, y = self.width//2, self.height//2
        X, Y = np.meshgrid(range(self.width), range(self.height),
                           indexing='ij')
        data[(X - x)**2 + (Y - y)**2 < self.max_size**2] = 1.0
        return Figure(data, x, y, self.max_size)


class SquareGenerator(FigureGenerator):

    def create(self):
        data = np.zeros((self.width, self.height))
        x, y = self.width//2, self.height//2
        size = self.max_size
        x_min = max((x - size, 0))
        x_max = min((x + size, self.width - 1))
        y_min = max((y - size, 0))
        y_max = min((y + size, self.height - 1))
        data[x_min:x_max, y_min:y_max] = 1.0
        return Figure(data, x, y, size)


class TriangleGenerator(FigureGenerator):

    def create(self):
        data = np.zeros((self.width, self.height))
        x, y = self.width//2, self.height//2
        size = 2*self.max_size
        for j in range(size):
            X = x + j - size//2
            for i in range(j):
               Y = y - j//2 + i
               data[X, Y] = 1.0
        return Figure(data, x, y, size)


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
