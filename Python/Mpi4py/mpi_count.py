#!/usr/bin/env python

from argparse import ArgumentParser
import os.path
from mpi4py import MPI


def count_chunk(file_name, file_pos, chunk_size):
    counter = {x: 0 for x in 'ACGT'}
    with open(file_name, 'r') as file:
        file.seek(file_pos)
        dna = file.read(chunk_size)
        for char in dna:
            if char in counter:
                counter[char] += 1
    return counter


def main():
    comm = MPI.COMM_WORLD
    size = comm.size
    rank = comm.rank
    if rank == 0:
        arg_parser = ArgumentParser(description=' nucleotide counter')
        arg_parser.add_argument('file', help='file to parse')
        options = arg_parser.parse_args()
        file_name = options.file
        file_size = os.path.getsize(options.file)
    else:
        file_name = None
        file_size = None
    file_name, file_size = comm.bcast((file_name, file_size), root=0)
    chunk_size = int(file_size/size) + 1
    offset = rank*chunk_size
    counter = count_chunk(file_name, offset, chunk_size)
    counters = comm.gather(counter, root=0)
    if rank == 0:
        total_nucl = 0
        total_counter = {x: 0 for x in 'ACGT'}
        for counter in counters:
            for nucl in counter:
                total_counter[nucl] += counter[nucl]
                total_nucl += counter[nucl]
        for nucl in sorted(total_counter):
            print('{0}: {1:d}'.format(nucl, total_counter[nucl]))
        print('total: {0}'.format(total_nucl))
    return 0

if __name__ == '__main__':
    main()
