#!/usr/bin/env python

import numpy as np
import scipy.io.wavfile as wav_io


def create_sin(time, freq, ampl, phase):
    return ampl*np.sin(2.0*np.pi*freq*time + phase)


def normalize(signal, ampl):
    min_signal = np.min(signal)
    max_signal = np.max(signal)
    return (signal*ampl)/(max_signal - min_signal)

if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    INPUT_ERROR = 1
    arg_parser = ArgumentParser(description='create a WAV file')
    arg_parser.add_argument('--duration', type=float, default=2.0,
                            help='signal duractino in secons')
    arg_parser.add_argument('--rate', type=int, default=44100,
                            help='sample rate in Hz')
    arg_parser.add_argument('--base', type=int, default=128,
                            help='base line amplitude')
    arg_parser.add_argument('--amplitude', type=float, default=30.0,
                            help='amplitued to normalize signal to')
    specs_group = arg_parser.add_argument_group()
    specs_group.add_argument('--freqs', metavar='FREQ', type=float,
                             nargs='+',
                             help='frequencies of sinusiodal components')
    specs_group.add_argument('--ampls', metavar='AMPL', type=float,
                             nargs='+',
                             help='amplitudes of sinusiodal components')
    specs_group.add_argument('--phases', metavar='PHASE', type=float,
                             nargs='*',
                             help='phases of sinusiodal components')
    arg_parser.add_argument('--specs_file', help='Wave specification file')
    arg_parser.add_argument('--wav', help='name of WAV file to write '
                                          'the signal to')
    arg_parser.add_argument('--out', action='store_true',
                            help='print signal to standard output')
    options = arg_parser.parse_args()
    if not options.specs_file:
        if len(options.freqs) != len(options.ampls):
            msg = '# error: {0:d} frequencies for {1:d} amplitudes\n'
            sys.stderr.write(msg.format(len(options.freqs),
                                        len(options.aompls)))
            sys.exit(INPUT_ERROR)
        freqs = np.array(options.freqs)
        ampls = np.array(options.ampls)
        if options.phases is not None:
            if len(options.phase) != len(options.freqs):
                msg = '# error: {0:d} frequencies for {1:d} phases\n'
                sys.stderr.write(msg.format(len(options.freqs),
                                            len(options.aompls)))
                sys.exit(INPUT_ERROR)
            phases = np.array(options.phases)
        else:
            phases = np.zeros(len(freqs))
    time = np.arange(options.rate*options.duration)/options.rate
    signal = np.zeros(len(time))
    for freq, ampl, phase in zip(freqs, ampls, phases):
        signal += create_sin(time, freq, ampl, phase)
    signal = options.base + normalize(signal, options.amplitude)
    if options.out:
        for t, s in zip(time, signal):
            print('{0:.6f}\t{1:.6f}'.format(t, s))
    if options.wav:
        wav_data = np.array(signal, dtype='uint8')
        wav_io.write(options.wav, options.rate, wav_data)
