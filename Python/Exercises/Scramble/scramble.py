#!/usr/bin/env python

from argparse import ArgumentParser
import re
import random
import sys


def tokenize(line):
    tokens = re.split(r'([A-Za-z]+)', line)
    return tokens


def neighbour_positions(length, nr_swaps):
    positions = list(range(length - 1))
    for _ in range(nr_swaps):
        src = random.choice(positions)
        positions.remove(src)
        dest = src + 1
        yield src, dest


def arbitrary_positions(length, nr_swaps):
    positions = list(range(length - 1))
    for _ in range(nr_swaps):
        src = random.choice(positions)
        positions.remove(src)
        dest = random.choice(positions)
        yield src, dest


def scramble_chars(token, max_nr_swaps, positions):
    if re.match(r'^[A-Za-z]+$', token) and len(token) > 1:
        nr_swaps = random.randrange(min(max_nr_swaps, len(token) - 1))
        for src, dest in positions(len(token), nr_swaps):
            chars = list(token)
            chars[dest], chars[src] = chars[src], chars[dest]
            token = ''.join(chars)
    return token


def scramble(input_file, output_file, nr_swaps, positions):
    with input_file as input:
        with output_file as output:
            for line in input:
                tokens = [scramble_chars(token, nr_swaps, positions)
                          for token in tokenize(line)]
                output.write(''.join(tokens))


def main():
    arg_parser = ArgumentParser(description='scramble words')
    arg_parser.add_argument('-n', dest='nr_swaps', default=2, type=int,
                            help='number of character to swap per word')
    arg_parser.add_argument('-mode', dest='mode', default='neighbors',
                            choices=['neighbours', 'arbitrary'],
                            help='scramble mode')
    options = arg_parser.parse_args()
    position_funcs = {
        'neighbors': neighbour_positions,
        'arbitrary': arbitrary_positions
    }
    scramble(sys.stdin, sys.stdout, options.nr_swaps,
             position_funcs[options.mode])
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
