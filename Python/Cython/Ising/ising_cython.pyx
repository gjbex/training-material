# cython: profile=True
# cython: linetrace=True

import math
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

    def step(self):
        cdef int i, j
        cdef double delta
        cdef double J = self._J
        cdef double H = self._H
        cdef int N = self._N
        cdef double T = self._T
        for i in range(self._N):
            for j in range(self._N):
                delta = 2.0*self._s[i][j]*(J*(self._s[i-1,j] +
                                              self._s[i,j-1] +
                                              self._s[i+1-N,j] +
                                              self._s[i,j+1-N]) +
                                           H)
                if (delta < 0.0 or
                        math.exp(-delta/T) > np.random.uniform()):
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
