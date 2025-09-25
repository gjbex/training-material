#!/usr/bin/env python3

from argparse import ArgumentParser
import random


def available_nucl(nucl_left):
    return [nucl for nucl in nucl_left if nucl_left[nucl] > 0]


def get_nucl(nucl_left):
    while True:
        if avail_nucls := available_nucl(nucl_left):
            nucl = random.choice(avail_nucls)
            nucl_left[nucl] -= 1
            yield nucl
        else:
            raise StopIteration()

    
if __name__ == '__main__':
    arg_parser = ArgumentParser(description='generate DNA fragment '
                                            'with given compositon')
    arg_parser.add_argument('--A', type=int, default=5,
                            help='number of A nucleotides')
    arg_parser.add_argument('--C', type=int, default=5,
                            help='number of C nucleotides')
    arg_parser.add_argument('--G', type=int, default=5,
                            help='number of G nucleotides')
    arg_parser.add_argument('--T', type=int, default=5,
                            help='number of T nucleotides')
    options = arg_parser.parse_args()
    nucl_left = {
        'A': options.A,
        'C': options.C,
        'G': options.G,
        'T': options.T,
    }
    for nucl in get_nucl(nucl_left):
        print(nucl, end='')
