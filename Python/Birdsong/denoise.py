#!/usr/bin/env python

import numpy as np
import scipy as sp
import scipy.signal
from scipy.io import wavfile

if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='filter signal')
    arg_parser.add_argument('--cutoff', type=float, default=0.4,
                            help='cutoff for lowpass filter, value '
                                 '[0, 1]')
    arg_parser.add_argument('--min_attenuation', type=float, default=30.0,
                            help='minimum attenuation for filter (dB)')
    arg_parser.add_argument('input', help='WAV input signal')
    arg_parser.add_argument('output', help='WAV output signal')
    options = arg_parser.parse_args()
    b, a = sp.signal.iirfilter(17, options.cutoff,
                               rs=options.min_attenuation,
                               btype='highpass', analog=False,
                               ftype='cheby2')
    rate, signal = wavfile.read(options.input)
    base = np.uint8(np.mean(signal))
    filtered_signal = sp.signal.filtfilt(b, a, signal)
    wav_signal = base + np.array(filtered_signal, dtype=np.uint8)
    wavfile.write(options.output, rate, wav_signal)
