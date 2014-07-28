#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import scipy
import scipy.stats
import matplotlib.pyplot as plt

arg_parser = ArgumentParser(description='plot data')
arg_parser.add_argument('file', help='data file to plot')
options = arg_parser.parse_args()

data = np.genfromtxt(options.file, dtype=[np.float64, np.float64],
                     delimiter=',', names=True)
plt.plot(data['x'], data['y'], 'ro')
slope, intercept, r, _, _ = scipy.stats.linregress(data['x'], data['y'])
fit = slope*data['x'] + intercept
plt.plot(data['x'], fit, 'b-')

plt.show()

