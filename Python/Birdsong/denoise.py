#!/usr/bin/env python

import numpy as np
from scipy import signal as signal_proc
from scipy.io import wavfile
import matplotlib.pyplot as plt

def plot_filter_response(b, a):
    w, h = signal_proc.freqs(b, a, 1000)
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.semilogx(w, 20 * np.log10(abs(h)))
    ax.set_title('frequency response')
    ax.set_xlabel('Frequency [radians / second]')
    ax.set_ylabel('Amplitude [dB]')
    # ax.axis((10, 1000, -100, 10))
    ax.grid(which='both', axis='both')

if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='filter signal')
    arg_parser.add_argument('--cutoff', type=float, default=0.4,
                            help='cutoff for lowpass filter, value '
                                 '[0, 1]')
    arg_parser.add_argument('--min_attenutation', type=float, default=30.0,
                            help='minimum attenuation for filter (dB)')
    arg_parser.add_argument('--plot', action='store_true',
                            help='plot filter response')
    arg_parser.add_argument('--input', help='WAV input signal')
    arg_parser.add_argument('--output', help='WAV input signal')
    options = arg_parser.parse_args()
    b, a = signal_proc.iirfilter(17, [options.cutoff], rp=1,
                                 rs=options.min_attenutation,
                                 btype='highpass', analog=False,
                                 ftype='butter')
    if options.input:
        rate, signal = wavfile.read(options.input)
        base = np.uint8(np.mean(signal))
        filtered_signal = signal_proc.filtfilt(b, a, np.array(signal))
        if options.output:
            wav_signal = base + np.array(filtered_signal, dtype=np.uint8)
            wavfile.write(options.output, rate, wav_signal)
    if options.plot:
        plot_filter_response(b, a)
        plt.show()
