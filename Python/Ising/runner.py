#!/usr/bin/env python

import sys

class UnknownQuantityError(Exception):

    def __init__(self, quantity):
        super(UnknownQuantityError, self).__init__()
        self.message = "unknown quantity '{0}'".format(quantity)


class NoConvergenceError(Exception):

    def __init__(self):
        super(NoConvergenceError, self).__init__()
        self.message = 'no convergence reached'

class NoRunnerStepsError(Exception):

    def __init__(self):
        super(NoConvergenceError, self).__init__()
        self.message = 'no number of steps specified for Runner'


class NoRunnerSystemError(Exception):

    def __init__(self):
        super(NoConvergenceError, self).__init__()
        self.message = 'no Ising system specified for Runner'


class BaseRunner(object):

    def __init__(self, ising=None, steps=None, is_verbose=True):
        super(BaseRunner, self).__init__()
        self._ising = ising
        self._steps = steps
        self._is_verbose = is_verbose
        self.reset()

    def set_system(self, ising):
        self._ising = ising

    def get(self, quantity):
        if quantity in self._quantities:
            return self._quantities[quantity]
        else:
            raise UnknownQuantityError(quantity)

    def quantities(self):
        return self._quantities.keys()

    def reset(self):
        self._quantities = {}

    def run(self, steps=None):
        if not steps:
            if self._steps:
                steps = self._steps
            else:
                raise NoRunnerStepsError()
        if not self._ising:
            raise NoRunnerSystemError()
        self._prologue()
        for t in xrange(1, steps + 1):
            if not self._pre_step(t):
                break
            self._ising.step()
            if not self._post_step(t):
                break
        self._epilogue()

    def _prologue(self):
        pass

    def _epilogue(self):
        pass

    def _pre_step(self, t):
        if self._is_verbose and t % 100 == 0:
            sys.stderr.write('# computing step {0:d}\n'.format(t))
        return True

    def _post_step(self, t):
        return True


import numpy as np
import scipy.stats

class SingleRunner(BaseRunner):

    def __init__(self, ising=None, steps=None, file_name=None,
                 is_verbose=True):
        super(SingleRunner, self).__init__(ising, steps, is_verbose)
        self._file_name = file_name
        self._data_fmt = '{0:d} {1:.4f} {2:.4f}\n'

    def _prologue(self):
        if self._file_name:
            self._file = open(file_name, 'w')
        else:
            self._file = sys.stdout
        self._file.write('t M E\n')
        self._file.write('# T = {0:.3f}\n'.format(self._ising.T()))
        self._file.write('# N = {0:d}\n'.format(self._ising.N()))
        self._file.write('# J = {0:.3f}\n'.format(self._ising.J()))
        self._file.write('# H = {0:.3f}\n'.format(self._ising.H()))
        self._file.write(self._data_fmt.format(0, self.
                                              _ising.magnetization(),
                                               self._ising.energy()))

    def _epilogue(self):
        if self._file_name:
            self._file.close()

    def _post_step(self, t):
        self._file.write(self._data_fmt.format(t, self.
                                              _ising.magnetization(),
                                               self._ising.energy()))
        return True


import os
import matplotlib.pyplot as plt

class MovieRunner(BaseRunner):

    def __init__(self, ising=None, steps=None, dir_name='Movie',
                 file_fmt='spins_{0:06d}.png', is_verbose=True):
        super(MovieRunner, self).__init__(ising, steps, is_verbose)
        self._dir_name = dir_name
        self._file_fmt = file_fmt

    def _prologue(self):
        if not os.path.exists(self._dir_name):
            os.makedirs(self._dir_name)        

    def _post_step(self, t):
        file_name = os.path.join(self._dir_name, self._file_fmt.format(t))
        spins = np.array([[self._ising.s(i, j)
                               for j in xrange(self._ising.N())]
                                    for i in xrange(self._ising.N())])
        plt.imsave(file_name, spins)
        return True


class ActivityHeatmapRunner(BaseRunner):

    def __init__(self, ising=None, steps=None, is_verbose=True,
                 burn_in=100):
        super(ActivityHeatmapRunner, self).__init__(ising, steps,
                                                    is_verbose)
        self._burn_in = burn_in

    def _prologue(self):
        self._quantities['heatmap'] = np.zeros((self._ising.N(),
                                                self._ising.N()),
                                               dtype=np.float32)

    def _post_step(self, t):
        if t > self._burn_in:
            for i in xrange(self._ising.N()):
                for j in xrange(self._ising.N()):
                    self._quantities['heatmap'][i, j] += self._ising.s(i, j)
        return True


class EquilibriumRunner(BaseRunner):
        
    def __init__(self, ising=None, steps=None, is_verbose=True,
                 burn_in=100, sample_period=10, window=20, max_slope=1e-4):
        super(EquilibriumRunner, self).__init__(ising, steps, is_verbose)
        self._burn_in = burn_in
        self._sample_period = sample_period
        self._window = window
        self._max_slope = max_slope
    
    def _prologue(self):
        self._t = []
        self._M = []

    def _post_step(self, t):
        if t > self._burn_in and t % self._sample_period == 0:
            if len(self._t) >= self._window:
                self._t.pop(0)
                self._M.pop(0)
            self._t.append(float(t))
            self._M.append(self._ising.magnetization())
            if len(self._t) == self._window:
                result = scipy.stats.linregress(self._t, self._M)
                self._quantities['M mean'] = result[1]
                self._quantities['M slope'] = result[0]
                self._quantities['M R^2'] = result[2]**2
                self._quantities['M stderr'] = result[4]
                if self._is_verbose:
                    msg = '# M slope = {0:.4e}\n'
                    sys.stderr.write(msg.format(self.get('M slope')))
                if np.abs(self.get('M slope')) <= self._max_slope:
                    self._quantities['steps'] = t
                    return False
        return True

    def _epilogue(self):
        result = scipy.stats.linregress(self._t, self._M)
        self._quantities['M mean'] = result[1]
        self._quantities['M slope'] = result[0]
        self._quantities['M R^2'] = result[2]**2
        self._quantities['M stderr'] = result[4]
        if np.abs(self.get('M slope')) > self._max_slope:
            raise NoConvergenceError()

