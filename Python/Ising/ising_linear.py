#!/usr/bin/env python
'''
Alternative implementation using 1D rather than 2D storage, slower
than the 2D version, but just to ensure that comparison to C++
implementation is fair.
'''

import numpy as np


class IsingSystem(object):

    def __init__(self, N, J=1.0, H=0.0, T=1.5):
        self._N = N
        self._J = J
        self._H = H
        self._T = T
        self._s = np.ones(N*N, dtype=np.int32)
        self._M = float(N*N)
        self._E = -J*N**2 - H*N

    def clone(self):
        return IsingSystem(self.N, self.J, self.H, self.T)

    def _delta_E(self, i, j):
        left = (self.N - 1 if i == 0 else i - 1)*self.N + j
        up = i*self.N + (self.N - 1 if j == 0 else j - 1)
        right = (0 if i == self.N - 1 else i + 1)*self.N + j
        down = i*self.N + (0 if j == self.N - 1 else j + 1)
        idx = i*self.N + j
        return 2.0*self._s[idx]*(self.J*(self._s[left] + self._s[up] +
                                         self._s[right] + self._s[down]) +
                                 self.H)

    def step(self):
        for i in range(self._N):
            for j in range(self._N):
                delta = self._delta_E(i, j)
                if (delta < 0.0 or
                        np.exp(-delta/self.T) > np.random.uniform()):
                    idx = i*self.N + j
                    self._s[idx] = -self._s[idx]
                    self._M += 2*self._s[idx]
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

    def magnetization(self):
        return self._M/self._N**2

    def energy(self):
        return self._E/self.N**2

    def init_random(self, seed):
        np.random.seed(seed)
