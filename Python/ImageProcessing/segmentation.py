#!/usr/bin/env python

from argparse import ArgumentParser
import matplotlib.pyplot as plt
import numpy as np
from skimage import data
from skimage.color import rgb2gray
from skimage.filters import gaussian
from skimage.segmentation import active_contour


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='experiment with active '
                                            'contours')
    arg_parser.add_argument('--alpha', type=float, default=0.015,
                            help='alpha value, higher is faster')
    arg_parser.add_argument('--beta', type=float, default=10.0,
                            help='beta value, higher is smoother')
    arg_parser.add_argument('--gamma', type=float, default=0.001,
                            help='gamma value, explicit time stepping')
    arg_parser.add_argument('--n', type=int, default=360,
                            help='number of points in snake')
    arg_parser.add_argument('--no-snake', action='store_true',
                            help='do not compute snake, only show initial '
                                'contour')
    options = arg_parser.parse_args()
    image = rgb2gray(data.astronaut())
    smoothed_image = gaussian(image, 3)
    x0, y0, radius = 220, 100, 100
    theta = np.linspace(0, 2*np.pi, options.n)
    x = x0 + radius*np.cos(theta)
    y = y0 + radius*np.sin(theta)
    initial_snake = np.array([x, y]).T

    if not options.no_snake:
        snake = active_contour(smoothed_image, initial_snake,
                               alpha=options.alpha, beta=options.beta,
                               gamma=options.gamma)

    figure = plt.figure(figsize=(7, 7))
    axis = figure.add_subplot(111)
    plt.gray()
    axis.imshow(image)
    axis.plot(initial_snake[:, 0], initial_snake[:, 1], '--b')
    if not options.no_snake:
        axis.plot(snake[:, 0], snake[:, 1], '-r', lw=1.5)
    axis.axis([0, image.shape[1], image.shape[0], 0])
    plt.show()
