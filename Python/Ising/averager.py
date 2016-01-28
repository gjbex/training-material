#!/usr/bin/env python

import multiprocessing
import sys
import numpy as np

from runner import UnknownQuantityError


class Averager(object):

    def __init__(self, runner, ising, is_verbose=1):
        self._is_verbose = is_verbose
        self._runner = runner
        self._ising = ising
        self._quantities = {}
        nr_cpus = multiprocessing.cpu_count()
        if is_verbose > 0:
            sys.stderr.write('# using {0:d} cores\n'.format(nr_cpus))
        self._pool = multiprocessing.Pool(nr_cpus)

    def average(self, runs):
        def do_run(run_nr, averager):
            if averager._is_verbose > 0:
                msg = '# run {0:d}\n'.format(run_nr)
                sys.stderr.write(msg)
            runner = averager._runner.clone()
            runner.set_system(averager._ising.clone())
            runner.run()
            quantities = {}
            for quantity in runner.quantities():
                quantities[quantity] = runner.get(quantity)
            return quantities
        run_input = [(run, self) for run in range(1, runs + 1)]
        results = self._pool.map(do_run, run_input)
        for result in results:
            for quantity in result:
                if quantity not in self.quantities():
                    self._quantities[quantity] = []
                self._quantities[quantity].append(result[quantity])

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
                    result[key] /= float(len(self._quantities[quantity]))
            else:
                result['mean'] = np.mean(self._quantities[quantity])
                result['std'] = np.std(self._quantities[quantity])
                result['min'] = np.min(self._quantities[quantity])
                result['max'] = np.max(self._quantities[quantity])
                result['N'] = len(self._quantities[quantity])
            return result
        else:
            raise UnknownQuantityError(quantity)
