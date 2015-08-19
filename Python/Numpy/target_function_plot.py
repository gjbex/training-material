#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser
    import numpy as np
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D
    from matplotlib import cm

    import optimization

# command line argument handling
    arg_parser = ArgumentParser(description='plot heatmap of 2D Gaussians')
    arg_parser.add_argument('file', nargs='?', help='file name for plot')
    arg_parser.add_argument('--points', type=int, default=200,
                            help='number of points on x and y axis')
    arg_parser.add_argument('--x_min', type=float, default=-1.25,
                            help='minimal x value')
    arg_parser.add_argument('--y_min', type=float, default=-1.25,
                            help='minimal y value')
    arg_parser.add_argument('--z_min', type=float, default=-1.0,
                            help='minimal z value')
    arg_parser.add_argument('--x_max', type=float, default=1.25,
                            help='maximum x value')
    arg_parser.add_argument('--y_max', type=float, default=1.25,
                            help='maximum y value')
    arg_parser.add_argument('--z_max', type=float, default=2.0,
                            help='maximum z value')
    options = arg_parser.parse_args()

# computations
    x = np.linspace(options.x_min, options.x_max, options.points)
    y = np.linspace(options.y_min, options.y_max, options.points)
    xx, yy = np.meshgrid(x, y)
    z = optimization.func(xx, yy)

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
