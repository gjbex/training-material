#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import scipy
import scipy.stats
import matplotlib.pyplot as plt

arg_parser = ArgumentParser(description='plot data')
arg_parser.add_argument('file', help='data file to plot')
arg_parser.add_argument('--out', help='output file')
options = arg_parser.parse_args()

data = np.genfromtxt(options.file, dtype=[np.float64, np.float64],
                     delimiter=',', names=True)
plt.plot(data['x'], data['y'], 'ro')
slope, intercept, r, _, _ = scipy.stats.linregress(data['x'], data['y'])
result_str = ('slope = {0:.3f}, ' +
              'intercept = {1:.3f}, ' +
              '(R = {0:.3e})').format(slope, intercept, r)
print(result_str)
fit = slope*data['x'] + intercept
plt.plot(data['x'], fit, 'b-')

if options.out:
    plt.savefig(options.out)
else:
    plt.show()
