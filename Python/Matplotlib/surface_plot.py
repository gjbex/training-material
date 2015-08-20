#!/usr/bin/env python

import numpy as np


def f(x, y, x0=0.0, freq=1.0, beta=0.5):
    r = np.sqrt((x - x0)**2 + y**2)
    return np.exp(-beta*r)*np.cos(2.0*np.pi*freq*r)

if __name__ == '__main__':
    from argparse import ArgumentParser
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D
    from matplotlib import cm

# command line argument handling
    arg_parser = ArgumentParser(description='plot heatmap of 2D Gaussians')
    arg_parser.add_argument('file', nargs='?', help='file name for plot')
    arg_parser.add_argument('--points', type=int, default=200,
                            help='number of points on x and y axis')
    arg_parser.add_argument('--x_min', type=float, default=-5.0,
                            help='minimal x value')
    arg_parser.add_argument('--y_min', type=float, default=-5.0,
                            help='minimal y value')
    arg_parser.add_argument('--z_min', type=float, default=-1.0,
                            help='minimal z value')
    arg_parser.add_argument('--x_max', type=float, default=5.0,
                            help='maximum x value')
    arg_parser.add_argument('--y_max', type=float, default=5.0,
                            help='maximum y value')
    arg_parser.add_argument('--z_max', type=float, default=1.0,
                            help='maximum z value')
    arg_parser.add_argument('--x0_1', type=float, default=-1.0,
                            help='x position of first maximum')
    arg_parser.add_argument('--x0_2', type=float, default=1.0,
                            help='x position of second maximum')
    arg_parser.add_argument('--f_1', type=float, default=1.0,
                            help='frequency of first maximum')
    arg_parser.add_argument('--f_2', type=float, default=0.5,
                            help='frequency of second maximum')
    options = arg_parser.parse_args()

# computations
    x = np.linspace(options.x_min, options.x_max, options.points)
    y = np.linspace(options.y_min, options.y_max, options.points)
    xx, yy = np.meshgrid(x, y)
    z = (f(xx, yy, x0=options.x0_1, freq=options.f_1) +
         f(xx, yy, x0=options.x0_2, freq=options.f_2))

# plot
    figure = plt.figure()
    axes = figure.gca(projection='3d')
    axes.set_xlim(options.x_min, options.x_max)
    axes.set_ylim(options.y_min, options.y_max)
    axes.set_zlim(options.z_min, options.z_max)
    surface = axes.plot_surface(xx, yy, z, rstride=4, cstride=4,
                                cmap=cm.coolwarm, linewidth=0)
    countours = axes.contour(x, y, z)
    figure.colorbar(surface)
    if options.file:
        plt.savefig(options.file)
    else:
        plt.show()
