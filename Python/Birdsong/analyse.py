#!/usr/bin/env python

import sys
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import scipy.io.wavfile as wav_io

def compute_spectrum(y, Fs):
    n = len(y) # lungime semnal
    k = np.arange(n)
    T = n/Fs
    frq = k/T # two sides frequency range
    Y = sp.fft(y)/n # fft computing and normalization
    return frq, Y

def filter_spectrum(frq, Y, level=0.001, window=5000):
    Y_filtered = np.array(Y)
    Y_filtered[np.abs(Y) < level] = 0.0
    half = len(Y_filtered)/2
    Y_filtered[half - window:half + window] = 0.0
    return Y_filtered

def compute_signal(frq, Y):
    y = (len(Y)*np.real(sp.ifft(Y))).astype(np.uint8)
    return y

def plot_spectrum(frq, Y, Fs, half_spectrum=True):
    n = len(frq)
    if half_spectrum:
        frq_half = frq[range(n/2)] # one side frequency range
        Y_half = Y[range(n/2)]
        plt.plot(frq_half, abs(Y_half), 'r') # plotting the spectrum
        plt.axis([0.0, Fs/2, 0.0, 0.15])
    else:
        plt.plot(frq, abs(Y), 'r') # plotting the spectrum
        plt.axis([0.0, 2*Fs, 0.0, 0.15])
    plt.xlabel('Freq (Hz)')
    plt.ylabel('|Y(freq)|')

Fs = 44100  # sampling rate

rate, y = wav_io.read(sys.argv[1])
timp = len(y)/44100.
t = np.linspace(0, timp, len(y))
frq, Y = compute_spectrum(y, Fs)
Y_filtered = filter_spectrum(frq, Y, level=0.01, window=10000)
y_filtered = compute_signal(frq, Y_filtered)
wav_io.write('new.wav', rate, y_filtered)

plt.subplot(2, 2, 1)
plt.plot(t, y)
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.subplot(2, 2, 2)
plot_spectrum(frq, Y, Fs)
plt.subplot(2, 2, 4)
plot_spectrum(frq, Y_filtered, Fs)
plt.subplot(2, 2, 3)
plt.plot(t, y_filtered)
plt.show()
