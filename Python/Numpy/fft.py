#!/usr/bin/env python

from argparse import ArgumentParser
from math import ceil
import numpy as np
import matplotlib.pyplot as plt

arg_parser = ArgumentParser(description='plot function and frequency '
                                        'spectrum')
arg_parser.add_argument('output', nargs='?', help='name of output file')
arg_parser.add_argument('--noise', type=float, default=0.05,
                        help='amplitude of normally distirbuted noise')
options = arg_parser.parse_args()


# amplitudes and frequencies of signals
ampl = np.array([1.0, 0.75, 0.5, 0.25])
freq = np.array([1.1, 1.9, 3.1, 4.5])

# total number of samples, and number of samples/second
n = 2**12
sample_freq = 2**7

# create figure environment
plt.figure(1)

# compute signal
t = np.arange(n, dtype=np.float64)
y = np.zeros(len(t))
for i in range(len(ampl)):
    y += ampl[i]*np.cos(2.0*np.pi*freq[i]*t/sample_freq)
noise_ampl = options.noise
y += noise_ampl*np.random.randn(len(t))

# plot signal
# plt.subplot(2, 1, 1)
plt.subplot(2, 1, 1)
plt.axis([0.0, 4000, -3.0, 3.0])
plt.plot(t, y)
plt.xlabel(r'$t$')
plt.ylabel(r'signal')

# create a periodic signal for FFT, and compute
t = np.arange(2*n, dtype=np.float64)
y = np.concatenate((y, y[::-1]))
f = np.fft.fftfreq(len(t), 1.0/sample_freq)
ty = np.fft.fft(y)
rnorm = np.max(np.abs(ty.real))
ty = ty/rnorm

# plot normalized frequency spectrum
max_freq = ceil(max(freq))
plt.subplot(2, 1, 2)
plt.axis([0.0, max_freq, 0.0, 1.0])
plt.plot(f[:n], np.abs(ty[:n]))
plt.xlabel(r'$f$')
plt.ylabel(r'spectrum')

# fix layout problems caused by default axes of subplot
plt.tight_layout()

# show plot, or save it to a file, if specified
if options.output:
    plt.savefig(options.output)
else:
    plt.show()
