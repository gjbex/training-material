Birdsong
========

Example code for signal processing using scipy.

What is it?
-----------
1. `analyse.py`: reads a WAV file, computes the frequency spectrum using
    FFT, and plots both signal and frequency spectrum.
1. `sound_plot.py`: module containing helper function to format plots.
1. `denoise.py`: reads a WAV file, applies a Chebychev 2 highpass filter,
   and writes a new WAV file with the filtered signal.
1. `create_signal.py`: crates a WAV file based on a signal composed of a
    sum of sinusoidal functions.
1. `Sounds`: contains a few WAV files of bird calls to experiment with.
