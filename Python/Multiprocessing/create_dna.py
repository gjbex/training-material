#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np


def main():
    arg_parser = ArgumentParser(description='create a DNA of specifed '
                                            'length')
    arg_parser.add_argument('--n', type=int, default=1000,
                            help='number of nucleotides')
    arg_parser.add_argument('--buffer_size', type=int, default=1000,
                            help='rng buffer size in lines')
    group = arg_parser.add_mutually_exclusive_group()
    group.add_argument('--line_width', type=int, default=80,
                       help='number of nucleotids per line')
    group.add_argument('--binary', action='store_true',
                       help='generate binary file')
    options = arg_parser.parse_args()
    alphabet = ['A', 'C', 'G', 'T']
    if options.binary:
        nr_nucl = options.n
        while nr_nucl - options.buffer_size > 0:
            print(''.join(np.random.choice(alphabet, options.buffer_size)),
                  end='')
            nr_nucl -= options.buffer_size
        print(''.join(np.random.choice(alphabet, nr_nucl)), end='')
    else:
        nr_lines = options.n//options.line_width
        remainder = options.n % options.line_width
        for line_nr in range(nr_lines):
            if line_nr % options.buffer_size == 0:
                buffer = np.random.choice(alphabet,
                                          (options.line_width,
                                           options.buffer_size))
            print(''.join(buffer[:, line_nr % options.buffer_size]))
        print(''.join(np.random.choice(alphabet, remainder)))


if __name__ == '__main__':
    main()
