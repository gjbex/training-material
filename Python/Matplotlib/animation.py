#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation


class CosDecay:

    def __init__(self, figure, x_min, x_max, nr_points=200):
        axes = figure.add_axes([0.1, 0.1, 0.8, 0.8])
        axes.set_xlim((x_min, x_max))
        axes.set_ylim((-1.0, 1.0))
        self._line, = axes.plot([], [])
        self._x = np.linspace(x_min, x_max, nr_points)

    def create_init(self):
        def init():
            self._line.set_data([], [])
            return [self._line]
        return init

    def create_animate(self):
        def animate(i):
            y = np.cos(2.0*np.pi*self._x)*np.exp(-0.005*self._x**2*i)
            self._line.set_data(self._x, y)
            return [self._line]
        return animate


arg_parser = ArgumentParser(description='create an MP4 animation of a '
                                        'function')
arg_parser.add_argument('file', help='MP4 output file name')
options = arg_parser.parse_args()

figure = plt.figure()

cosDecay = CosDecay(figure, -6.0*np.pi, 6.0*np.pi, 2000)

init_f = cosDecay.create_init()
anim_f = cosDecay.create_animate()

anim = animation.FuncAnimation(figure, anim_f, init_func=init_f,
                               frames=300, interval=20, blit=True)
anim.save(options.file, fps=2, writer=animation.AVConvWriter())
