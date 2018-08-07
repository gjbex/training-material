#!/usr/bin/env python

from argparse import ArgumentParser
import matplotlib.pyplot as plt

from history_utils import plot_history_file


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='show training history')
    arg_parser.add_argument('file', help='HDF5 file containing the '
                                         'history')
    options = arg_parser.parse_args()
    plot_history_file(options.file)
    plt.show()
