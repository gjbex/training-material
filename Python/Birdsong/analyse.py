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

def filter_spectrum(frq, Y, level=0.001, window=5000):
    Y_filtered = np.array(Y)
    Y_filtered[np.abs(Y) < level] = 0.0
    half = len(Y_filtered)/2
    Y_filtered[half - window:half + window] = 0.0
    return Y_filtered

def compute_signal(freq, Y):
    y = (len(Y)*np.real(sp.ifft(Y))).astype(np.uint8)
    return y

if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    import sound_plot
    arg_parser = ArgumentParser(description='analyse WAV file')
    arg_parser.add_argument('wav_file', help='WAV file to analyse')
    arg_parser.add_argument('--filter', action='store_true',
                            help='perform filter operations')
    arg_parser.add_argument('--filtered_wav_file',
                            help='WAV file to write the filtered signal')
    options = arg_parser.parse_args()
    nr_cols = 2 if options.filter else 1

    rate, signal = wav_io.read(options.wav_file)
    n = len(signal)
    time = np.linspace(0, float(n)/rate, n)
    freq, Y = compute_spectrum(signal, rate)
# plot signal and spectrum
    plt.subplot(2, nr_cols, 1)
    sound_plot.plot_signal(time, signal)
    plt.subplot(2, nr_cols, 2)
    sound_plot.plot_spectrum(freq, Y, rate)

    if options.filter:
        Y_filtered = filter_spectrum(freq, Y, level=0.01, window=10000)
        signal_filtered = compute_signal(freq, Y_filtered)
        if options.filtered_wav_file:
            wav_io.write(options.filtered_wav_file, rate, signal_filtered)
# plot filtered signal and spectrum
        plt.subplot(2, nr_cols, 4)
        sound_plot.plot_spectrum(freq, Y_filtered, rate)
        plt.subplot(2, nr_cols, 3)
        sound_plot.plot_signal(time, signal_filtered)

    plt.show()
