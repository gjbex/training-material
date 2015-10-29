import matplotlib.pyplot as plt


def plot_signal(time, signal):
    plt.plot(time, signal)
    plt.xlabel(r'$t$')
    plt.ylabel(r'$A(t)$')


def plot_spectrum(freq, spectrum, rate, half_spectrum=True,
                  spectrum_max=0.15):
    if half_spectrum:
        n = len(freq)
        freq_half = freq[list(range(n//2))]
        spectrum_half = spectrum[list(range(n//2))]
# plotting the spectrum
        plt.plot(freq_half, abs(spectrum_half), 'r')
        plt.axis([0.0, rate/2.0, 0.0, spectrum_max])
    else:
        plt.plot(freq, abs(spectrum), 'r')
        plt.axis([0.0, 2.0*rate, 0.0, spectrum_max])
    plt.xlabel(r'$f$ (Hz)')
    plt.ylabel(r'|P(f)|')
