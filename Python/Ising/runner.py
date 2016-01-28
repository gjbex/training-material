#!/usr/bin/env python

import os
import sys
import numpy as np
import scipy.stats
import matplotlib.pyplot as plt
from domain_counter import compute_domain_sizes


class UnknownQuantityError(Exception):
    '''Thrown when a Runner is queried for a non-existing quantiy'''
    def __init__(self, quantity):
        super(UnknownQuantityError, self).__init__()
        self.message = "unknown quantity '{0}'".format(quantity)


class NoConvergenceError(Exception):
    '''Thrown when no convergence is reached for the specified steps'''
    def __init__(self):
        super(NoConvergenceError, self).__init__()
        self.message = 'no convergence reached'


class NoRunnerStepsError(Exception):
    '''Thrown when no number of steps was specified

    Since the number of steps to take can be specified either on
    construction of the object, or as argument of the run options, it
    may well be forgotten twice.'''
    def __init__(self):
        super(NoRunnerStepsError, self).__init__()
        self.message = 'no number of steps specified for Runner'


class NoRunnerSystemError(Exception):
    '''Thrown when no Ising model was specified

    Since the Ising system can be set either on construction of the Runner,
    or by calling the set_system() method, it may be forgotten twice.'''
    def __init__(self):
        super(NoRunnerSystemError, self).__init__()
        self.message = 'no Ising system specified for Runner'


class BaseRunner(object):
    '''Runner base class

    Base class that more useful Runners extend.  It defines the base
    constructor, the mechanism to keep track of quantities to be evaluated
    at each step, and the base functions that are exectued befor a run
    starts, before a step is computed, after a step is computed, and at
    the end of a run.'''
    def __init__(self, ising=None, steps=None, is_verbose=1):
        '''
        Constructor, optionally set the Ising system to run (can also be
        done via set_system() method, and the number of steps (can also be
        done as argument to the run() method.
        '''
        super(BaseRunner, self).__init__()
        self._ising = ising
        self._steps = steps
        self._is_verbose = is_verbose
        self.reset()

    def clone(self):
        return BaseRunner(self._ising, self._steps, self._is_verbose)

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
        for t in range(1, steps + 1):
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
        if self._is_verbose > 0 and t % 100 == 0:
            sys.stderr.write('# computing step {0:d}\n'.format(t))
        return True

    def _post_step(self, t):
        return True


class SingleRunner(BaseRunner):

    def __init__(self, ising=None, steps=None, file_name=None,
                 is_verbose=1):
        super(SingleRunner, self).__init__(ising, steps, is_verbose)
        self._file_name = file_name
        self._data_fmt = '{0:d} {1:.4f} {2:.4f}\n'

    def clone(self):
        return SingleRunner(self._ising, self._steps, self._file_name,
                            self._is_verbose)

    def _prologue(self):
        if self._file_name:
            self._file = open(self._file_name, 'w')
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


class MovieRunner(BaseRunner):

    def __init__(self, ising=None, steps=None, dir_name='Movie',
                 file_fmt='spins_{0:06d}.png', is_verbose=1):
        super(MovieRunner, self).__init__(ising, steps, is_verbose)
        self._dir_name = dir_name
        self._file_fmt = file_fmt

    def clone(self):
        return MovieRunner(self._ising, self._steps, self._dir_name,
                           self._file_fmt, self._is_verbose)

    def _prologue(self):
        if not os.path.exists(self._dir_name):
            os.makedirs(self._dir_name)

    def _post_step(self, t):
        file_name = os.path.join(self._dir_name, self._file_fmt.format(t))
        spins = np.array([[self._ising.s(i, j)
                           for j in range(self._ising.N())]
                          for i in range(self._ising.N())])
        plt.imsave(file_name, spins)
        return True


class Visualize3DRunner(BaseRunner):

    header = '''<?xml version="1.0" ?>
<Xdmf Version="2.0">
  <Domain Name="domain">
    <Grid GridType="Uniform" Name="mesh">
      <Topology Dimensions="{N:d} {N:d} {steps:d}"
                Name="topology" TopologyType="3DCoRectMesh"/>
      <Geometry GeometryType="ORIGIN_DxDyDz" Name="geometry">
        <DataItem Dimensions="3" Format="XML">
          0.0 0.0 0.0
        </DataItem>
        <DataItem Dimensions="3" Format="XML">
          {XY:.1f} {XY:.1f} {Z:.1f}
        </DataItem>
      </Geometry>
      <Attribute Center="Node" Name="temperature">
        <DataItem Dimensions="{N:d} {N:d} {steps:d}" Format="XML">
'''
    footer = '''       </DataItem>
      </Attribute>
    </Grid>
  </Domain>
</Xdmf>'''

    def __init__(self, ising=None, steps=None, file_name='ising_run.xmdf',
                 is_verbose=1):
        super(Visualize3DRunner, self).__init__(ising, steps, is_verbose)
        self._file_name = open(file_name, 'w')

    def _prologue(self):
        self._file = open(self._file_name, 'w')
        self._file.write(Visualize3DRunner.header.format(
            N=self._ising.N(), steps=self._steps,
            XY=np.log10(self._ising.N()),
            Z=np.log10(self._steps))
        )

    def _post_step(self, t):
        for i in range(self._ising.N()):
            for j in range(self._ising.N()):
                self._file.write('{0:d}\n'.format(self._ising.s(i, j)))
        return True

    def _epilogue(self):
        self._file.write(Visualize3DRunner.footer)
        self._file.close()


class ActivityHeatmapRunner(BaseRunner):

    def __init__(self, ising=None, steps=None, is_verbose=1,
                 burn_in=100):
        super(ActivityHeatmapRunner, self).__init__(ising, steps,
                                                    is_verbose)
        self._burn_in = burn_in

    def clone(self):
        return ActivityHeatmapRunner(self._ising, self._steps,
                                     self._is_verbose)

    def _prologue(self):
        self._quantities['heatmap'] = np.zeros((self._ising.N(),
                                                self._ising.N()),
                                               dtype=np.float32)

    def _post_step(self, t):
        if t > self._burn_in:
            for i in range(self._ising.N()):
                for j in range(self._ising.N()):
                    self._quantities['heatmap'][i, j] += self._ising.s(i, j)
        return True


class EquilibriumRunner(BaseRunner):

    def __init__(self, ising=None, steps=None, is_verbose=1,
                 burn_in=100, sample_period=10, window=20, max_slope=1e-4):
        super(EquilibriumRunner, self).__init__(ising, steps, is_verbose)
        self._burn_in = burn_in
        self._sample_period = sample_period
        self._window = window
        self._max_slope = max_slope

    def clone(self):
        return EquilibriumRunner(self._ising, self._steps, self._is_verbose,
                                 self._burn_in, self._sample_period,
                                 self._window, self._max_slope)

    def _prologue(self):
        self._t = []
        self._M = []
        self._E = []
        self._E2 = []

    def _collect(self, t):
        if len(self._t) >= self._window:
            self._t.pop(0)
            self._M.pop(0)
            self._E.pop(0)
            self._E2.pop(0)
        self._t.append(float(t))
        self._M.append(self._ising.magnetization())
        self._E.append(self._ising.energy())
        self._E2.append(self._ising.energy()**2)

    def _post_step(self, t):
        if t > self._burn_in and t % self._sample_period == 0:
            self._collect(t)
            if len(self._t) == self._window:
                result = scipy.stats.linregress(self._t, self._M)
                slope = result[0]
                if np.abs(slope) <= self._max_slope:
                    self._quantities['steps'] = t
                    return False
        return True

    def _epilogue(self):
        result = scipy.stats.linregress(self._t, self._M)
        self._quantities['M mean'] = result[1]
        self._quantities['M slope'] = result[0]
        self._quantities['M R^2'] = result[2]**2
        self._quantities['M stderr'] = result[4]
        result = scipy.stats.linregress(self._t, self._E)
        self._quantities['E mean'] = result[1]
        self._quantities['E slope'] = result[0]
        self._quantities['E R^2'] = result[2]**2
        self._quantities['E stderr'] = result[4]
        self._quantities['deltaE^2'] = (np.mean(self._E2) -
                                        np.mean(self._E)**2)
        if np.abs(self.get('M slope')) > self._max_slope:
            raise NoConvergenceError()


class DomainSizeRunner(EquilibriumRunner):
    '''
    Collect information no domain size distribution.
    '''

    def __init__(self, ising=None, steps=None, is_verbose=1,
                 burn_in=100, sample_period=10, window=20, max_slope=1e-4):
        super(DomainSizeRunner, self).__init__(ising, steps, is_verbose,
                                               burn_in, sample_period,
                                               window, max_slope)

    def clone(self):
        return DomainSizeRunner(self._ising, self._steps, self._is_verbose,
                                self._burn_in, self._sample_period,
                                self._window, self._max_slope)

    def _prologue(self):
        super(DomainSizeRunner, self)._prologue()
        self._domains = []

    def _collect(self, t):
        super(DomainSizeRunner, self)._collect(t)
        if len(self._domains) >= self._window:
            self._domains.pop(0)
        domains = compute_domain_sizes(self._ising)
        self._domains.append(domains)

    def _epilogue(self):
        super(DomainSizeRunner, self)._epilogue()
        sizes = {}
        for domains in self._domains:
            for domain in domains:
                if domain not in sizes:
                    sizes[domain] = 0.0
                sizes[domain] += 1.0
        for size in sizes:
            sizes[size] /= len(self._domains)
        self._quantities['domains'] = sizes
