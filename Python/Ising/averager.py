#!/usr/bin/env python

import sys
import numpy as np

from ising_cxx import IsingSystem
from runner import UnknownQuantityError

class Averager(object):

    def __init__(self, runner, ising, is_verbose=1):
        self._is_verbose = is_verbose
        self._runner = runner
        self._ising = ising
        self._quantities = {}

    def average(self, runs):
        for r in xrange(1, runs + 1):
            if self._is_verbose > 0:
                msg = '# run {0:d}\n'.format(r)
                sys.stderr.write(msg)
            self._runner.set_system(self._ising.clone())
            self._runner.run()
            for quantity in self._runner.quantities():
                if quantity not in self.quantities():
                    self._quantities[quantity] = []
                self._quantities[quantity].append(self._runner.get(quantity))
            self._runner.reset()

    def quantities(self):
        return self._quantities.keys()

    def get(self, quantity):
        if quantity in self._quantities:
            result = {}
            if type(self._quantities[quantity][0]) == dict:
                for dictionary in self._quantities[quantity]:
                    for key in dictionary:
                        if key not in result:
                            result[key] = 0
                        result[key] += dictionary[key]
                for key in result:
                    result[key] /= len(self._quantities[quantity])
            else:
                result['mean'] = np.mean(self._quantities[quantity])
                result['std'] = np.std(self._quantities[quantity])
                result['min'] = np.min(self._quantities[quantity])
                result['max'] = np.max(self._quantities[quantity])
                result['N'] = len(self._quantities[quantity])
            return result
        else:
            raise UnknownQuantityError(quantity)

