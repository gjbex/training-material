#!/usr/bin/env python

import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import scipy.io.wavfile as wav_io


def compute_spectrum(signal, rate):
    n = len(signal)
    k = np.arange(n)
    T = n/rate
    freq = k/T
    Y = sp.fft(signal)/n
    return freq, Y

if __name__ == '__main__':
    from argparse import ArgumentParser
    import sound_plot
    arg_parser = ArgumentParser(description='analyse WAV file')
    arg_parser.add_argument('wav_file', help='WAV file to analyse')
    options = arg_parser.parse_args()
    nr_cols = 1

    rate, signal = wav_io.read(options.wav_file)
    n = len(signal)
    time = np.linspace(0, float(n)/rate, n)
    freq, Y = compute_spectrum(signal, rate)
# plot signal and spectrum
    plt.subplot(2, nr_cols, 1)
    sound_plot.plot_signal(time, signal)
    plt.subplot(2, nr_cols, 2)
    sound_plot.plot_spectrum(freq, Y, rate)
    plt.show()
