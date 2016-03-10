#!/usr/bin/env python

from argparse import ArgumentParser
import multiprocessing
import os.path
import sys


def init_counter():
    return {'A': 0, 'C': 0, 'G': 0, 'T': 0}


def count_chunk(args):
    file_name, file_pos, chunk_size = args
    counter = init_counter()
    with open(file_name, 'r') as file:
        file.seek(file_pos)
        dna = file.read(chunk_size)
        for char in dna:
            if char in counter:
                counter[char] += 1
    return counter


def count_nucl(file_name, pool_size):
    file_size = os.path.getsize(file_name)
    chunk_size = file_size//pool_size + 1
    offsets = range(0, file_size, chunk_size)
    args = [(file_name, offset, chunk_size) for offset in offsets]
    with multiprocessing.Pool(pool_size) as pool:
        counters = pool.map(count_chunk, args)
    counter = init_counter()
    for part_counter in counters:
        for nucl in part_counter:
            counter[nucl] += part_counter[nucl]
    return counter


def main():
    arg_parser = ArgumentParser(description=' nucleotide counter')
    arg_parser.add_argument('file', help='file to parse')
    arg_parser.add_argument('--np', dest='pool_size', type=int,
                            default=1, help='number of processes')
    options = arg_parser.parse_args()
    counter = count_nucl(options.file, options.pool_size)
    total_nucl = 0
    for nucl in sorted(counter):
        total_nucl += counter[nucl]
        print('{0}: {1:d}'.format(nucl, counter[nucl]))
    print('total: {0:d}'.format(total_nucl))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
