#!/usr/bin/env python

import numpy as np

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
        return self.J*self._s[i][j]*(self._s[left] + self._s[up] +
                                     self._s[right] + self._s[down] +
                                     2.0*self.H)

    def step(self):
        for i in xrange(self._N):
            for j in xrange(self._N):
                delta = self._delta_E(i, j)
                if delta < 0.0 or np.exp(-delta/self.T) > np.random.uniform():
                    self._s[i, j] = -self._s[i, j]
                    self._M += 2*self._s[i, j]
                    self._E += delta
    
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
    def magentization(self):
        return self._M/self._N**2

    @property
    def energy(self):
        return self._E/self.N**2

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
    print '# T = {0:.3f}'.format(options.T)
    print '# N = {0:d}'.format(options.N)
    print '# J = {0:.3f}'.format(options.J)
    print '# H = {0:.3f}'.format(options.H)
    ising = IsingSystem(options.N, J=options.J, H=options.H, T=options.T)
    print 't,M,E'
    print '{0:d},{1:.4f},{2:.4f}'.format(0, ising.magentization,
                                         ising.energy)
    for t in xrange(1, options.steps + 1):
        ising.step()
        print '{0:d},{1:.4f},{2:.4f}'.format(t, ising.magentization,
                                             ising.energy)

