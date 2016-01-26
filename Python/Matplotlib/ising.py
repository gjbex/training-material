#!/usr/bin/env python

import numpy as np
import scipy.optimize as opt
import matplotlib.pyplot as plt

imgfile_fmt = '{0:s}-{1:04d}.png'
imgpatt_fmt = '{0:s}-*.png'
moviefile_fmt = '{0:s}.gif'


def create_sigmoid(beta):
    def f(x):
        return np.tanh(4*beta*x)
    return f


def find_roots(f, x_low=-5.0, x_high=5.0):
    def f_opt(X):
        return f(X[0]) - X[0]
    r1 = opt.root(f_opt, np.array([x_low]))
    r2 = opt.root(f_opt, np.array([x_high]))
    return np.array([r1.x[0], 0.0, r2.x[0]])


def create_plot(beta, i, betas, magnetization, options):
    sigmoid = create_sigmoid(beta)
    x = np.linspace(-options.x_max, options.x_max, options.points)
    y = sigmoid(x)
    plt.plot(x, y)
    plt.plot(x, x)
    plt.xlabel(r'$m$')
    plt.ylabel(r'$\tanh(4\beta m)$')
    plt.axis([-options.x_max, options.x_max, -1.1, 1.1])
    plt.text(-options.x_max + 0.5, 0.5, r'$\beta = {0:.5f}$'.format(beta),
             fontsize=16)
# plot roots
    roots = find_roots(sigmoid)
    values = sigmoid(roots)
    plt.plot(roots, values, 'ro')
# plot magnetization
    betas.append(beta)
    for k, root in enumerate(roots):
        magnetization[k].append(root)
    plt.axes([0.6, 0.2, 0.35, 0.35])
    T = 1.0/np.array(betas)
    plt.axis([0.0, 1.0/options.beta_min, -1.1, 1.1])
    for magn in magnetization:
        plt.plot(T, np.array(magn), 'b-')
    plt.xlabel(r'$T$')
    plt.ylabel(r'$m$')
    plt.savefig(imgfile_fmt.format(options.file_base, i))
    plt.clf()

if __name__ == '__main__':
    from argparse import ArgumentParser
    import os
    import subprocess
    import sys

    arg_parser = ArgumentParser(description='create movie for Ising mean '
                                            'field equation')
    arg_parser.add_argument('--x_max', type=float, default=1.5,
                            help='x-value range')
    arg_parser.add_argument('--points', type=int, default=200,
                            help='number of plot points to use')
    arg_parser.add_argument('--beta_min', type=float, default=1.0/6.0,
                            help='minimum beta value')
    arg_parser.add_argument('--beta_max', type=float, default=3.0,
                            help='maximum beta value')
    arg_parser.add_argument('--alpha', type=float, default=2.0,
                            help='value in beta(i+1) = 1/4 '
                                 '+ (1/4 - beta(i))/alpha')
    arg_parser.add_argument('--file_base', default='ising_magnetization',
                            help='base name to use for file')
    arg_parser.add_argument('--steps', type=int, default=20,
                            help='number of plot points to use')
    arg_parser.add_argument('--keep_last', action='store_true',
                            help='keep last image')
    arg_parser.add_argument('--keep_all', action='store_true',
                            help='keep all images')
    options = arg_parser.parse_args()

    betas = []
    magnetization = [[], [], []]
    i = 1
    beta = options.beta_max
    while beta >= 0.25001 and i <= options.steps:
        msg_str = 'creating plot {0:d} for beta = {1:.5f}\n'.format(i, beta)
        sys.stderr.write(msg_str)
        create_plot(beta, i, betas, magnetization, options)
        i += 1
        beta = 0.25 + (beta - 0.25)/options.alpha
    beta = 0.25
    while beta >= options.beta_min and i <= 2*options.steps:
        msg_str = 'creating plot {0:d} for beta = {1:.5f}\n'.format(i, beta)
        sys.stderr.write(msg_str)
        create_plot(beta, i, betas, magnetization, options)
        i += 1
        beta -= 0.025
    total_figures = i - 1
    sys.stderr.write('creating movie GIF\n')
    try:
        status = subprocess.call(['convert', '-set', 'delay', '100',
                                  imgpatt_fmt.format(options.file_base),
                                  moviefile_fmt.format(options.file_base)])
    except subprocess.CalledProcessError as e:
        sys.stderr.write('# error: {0}\n'.format(e.message))
        sys.exit(status)
    if not options.keep_all:
        for i in range(1, total_figures):
            os.remove(imgfile_fmt.format(options.file_base, i))
        if not options.keep_last:
            os.remove(imgfile_fmt.format(options.file_base, total_figures))
