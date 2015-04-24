#!/usr/bin/env python

import sys
import numpy as np
import scipy as sp
import pylab
import scipy.io.wavfile as wavio

def plotSpectru(y, Fs):
    n = len(y) # lungime semnal
    k = sp.arange(n)
    T = float(n)/Fs
    frq = k/T # two sides frequency range
    frq = frq[range(n/2)] # one side frequency range
    # print frq

    Y = sp.fft(y)/n # fft computing and normalization
    Y = Y[range(n/2)]
        
    pylab.plot(frq[1:], abs(Y[1:]), 'r') # plotting the spectrum
    pylab.xlabel('Freq (Hz)')
    pylab.ylabel('|Y(freq)|')

Fs = 44100  # sampling rate

sys.stderr.write('start reading data...\n')
rate, data = wavio.read(sys.argv[1])
sys.stderr.write('done reading data...\n')
print  np.shape(data)
y = data[:]
lungime = len(y)
timp = len(y)/44100.
t = np.linspace(0, timp, len(y))

pylab.subplot(2, 1, 1)
pylab.plot(t, y)
pylab.xlabel('Time')
pylab.ylabel('Amplitude')
pylab.subplot(2, 1, 2)
plotSpectru(y, Fs)
pylab.show()
