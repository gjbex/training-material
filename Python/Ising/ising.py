#!/usr/bin/env python

import numpy as np


class IsingSystem(object):

    def __init__(self, N, J=1.0, H=0.0, T=1.5):
        self._N = N
        self._J = J
        self._H = H
        self._T = T
        self._s = np.ones((N, N), dtype=np.int32)
        self._M = float(N*N)
        self._E = -J*N**2 - H*N

    def clone(self):
        return IsingSystem(self.N(), self.J(), self.H(), self.T())

    def _delta_E(self, i, j):
        left = (i - 1, j)
        up = (i, j - 1)
        right = (i + 1 - self._N, j)
        down = (i, j + 1 - self._N)
        return 2.0*self._s[i][j]*(self._J*(self._s[left] + self._s[up] +
                                           self._s[right] + self._s[down]) +
                                  self._H)

    def step(self):
        for i in range(self._N):
            for j in range(self._N):
                delta = self._delta_E(i, j)
                if (delta < 0.0 or
                        np.exp(-delta/self._T) > np.random.uniform()):
                    self._s[i, j] = -self._s[i, j]
                    self._M += 2*self._s[i, j]
                    self._E += delta

    def T(self):
        return self._T

    def N(self):
        return self._N

    def J(self):
        return self._J

    def H(self):
        return self._H

    def s(self, i, j):
        return self._s[i, j]

    def magnetization(self):
        return self._M/self._N**2

    def energy(self):
        return self._E/self._N**2

    def init_random(self, seed):
        np.random.seed(seed)
