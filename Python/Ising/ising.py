#!/usr/bin/env python

import numpy as np
import scipy.stats

def do_nothing(ising, options):
    pass

def step_do_nothing(step, ising, options):
    pass

class IsingSystem(object):

    def __init__(self, N, J = 1.0, H = 0.0, T = 1.5):
        self._N = N
        self._J = J
        self._H = H
        self._T = T
        self._s = np.ones((N, N), dtype=np.int32)
        self._M = float(N*N)
        self._E = -J*N**2/2.0 - H*N

    def _delta_E(self, i, j):
        left = (i - 1, j)
        up = (i, j - 1)
        right = (i + 1 - self.N, j)
        down = (i, j + 1 - self.N)
        return 2*self.J*self._s[i][j]*(self._s[left] + self._s[up] +
                                       self._s[right] + self._s[down] +
                                       self.H)

    def step(self):
        for i in xrange(self._N):
            for j in xrange(self._N):
                delta = self._delta_E(i, j)
                if (delta < 0.0 or
                    np.exp(-delta/self.T) > np.random.uniform()):
                    self._s[i, j] = -self._s[i, j]
                    self._M += 2*self._s[i, j]
                    self._E += delta
    
    def run(self, t_max, prologue=do_nothing, epilogue=do_nothing,
            pre_step=step_do_nothing, post_step=step_do_nothing,
            options={}):
        prologue(self, options)
        for t in xrange(1, t_max + 1):
            pre_step(t, self, options)
            ising.step()
            post_step(t, self, options)
        epilogue(self, options)

    @property
    def T(self):
        return self._T

    @property
    def N(self):
        return self._N

    @property
    def J(self):
        return self._J

    @property
    def H(self):
        return self._H

    @property
    def magnetization(self):
        return self._M/self._N**2

    @property
    def energy(self):
        return self._E/self.N**2


def print_header(ising, options):
    print 't,M,E'
    print '# T = {0:.3f}'.format(ising.T)
    print '# N = {0:d}'.format(ising.N)
    print '# J = {0:.3f}'.format(ising.J)
    print '# H = {0:.3f}'.format(ising.H)
    print '{0:d},{1:.4f},{2:.4f}'.format(0, ising.magnetization,
                                         ising.energy)

def print_data(t, ising, options):
    print '{0:d},{1:.4f},{2:.4f}'.format(t, ising.magnetization,
                                         ising.energy)

def init_average(ising, options):
    options['t'] = []
    options['M'] = []
    options['E'] = []

def update_average(t, ising, options):
    if t > 100 and t % 10 == 0:
        options['t'].append(float(t))
        options['M'].append(ising.magnetization)

def compute_average(ising, options):
    slope, intercept, r, _, _ = scipy.stats.linregress(options['t'],
                                                       options['M'])
    options['M_mean'] = intercept
    options['M_slope'] = slope
    options['M_r^2'] = r**2
    
def show_progress(t, ising, options):
    if t % 100 == 0:
        print '# processing step {0:d}'.format(t)


if __name__ == '__main__':

    from argparse import ArgumentParser
    import sys

    arg_parser = ArgumentParser(description='2D ising system simulaation')
    arg_parser.add_argument('--N', type=int, default=10,
                            help='system size, i.e., N x N')
    arg_parser.add_argument('--J', type=float, default=1.0,
                            help='spin-spin interactino energy')
    arg_parser.add_argument('--H', type=float, default=0.0,
                            help='magnetic field')
    arg_parser.add_argument('--T', type=float, default=1.5,
                            help='temerature in units k_b')
    arg_parser.add_argument('--steps', type=int, default=10,
                            help='number of simulation steps')
    options = arg_parser.parse_args()
    ising = IsingSystem(options.N, J=options.J, H=options.H, T=options.T)
#    ising.run(options.steps, prologue=print_header, pre_step=print_data)
    run_options = {}
    ising.run(options.steps, prologue=init_average,
              pre_step=show_progress, post_step=update_average,
              epilogue=compute_average, options=run_options)
    print 'M = {M_mean:.4f}, slope M = {M_slope:.4f}, R^2 = {M_r^2:.4f}'.format(**run_options)

