#!/usr/bin/env python
"""
This script is for illustration purposes only, it ignores quite a number
of natural language features, so it should be considered an example only
in a technical sense.
"""


from argparse import ArgumentParser
import os.path
import sys
from mpi4py import MPI

terminators = {'.', '?', '!'}


def extract_prefix(file_name, start_pos, end_pos):
    global terminators
    prefix_str = ''
    index = 0
    with open(file_name, 'r') as file:
        file.seek(start_pos)
        if start_pos < end_pos:
            c = file.read(1)
            if not c.isupper():
                file.seek(start_pos)
                while index + start_pos < end_pos:
                    c = file.read(1)
                    prefix_str += c
                    index += 1
                    if c in terminators:
                        break
        return (prefix_str, start_pos + index)


def extract_suffix(file_name, start_pos, end_pos):
    global terminators
    suffix_str = ''
    with open(file_name, 'r') as file:
        file.seek(end_pos)
        if end_pos >= start_pos:
            c = file.read(1)
            if c not in terminators:
                file.seek(end_pos)
                while end_pos >= start_pos:
                    c = file.read(1)
                    if c in terminators:
                        break
                    suffix_str = c + suffix_str
                    current_pos = file.tell()
                    file.seek(current_pos - 2)
                    end_pos -= 1
        return (suffix_str, end_pos)


def count_sentences(file_name, start_pos, end_pos):
    """Parse a given string, returning the number of sentences, as well
       as the prefix to the first sentence, as well as the suffix to the
       last."""
    global terminators
    with open(file_name, 'r') as file:
        file.seek(start_pos)
        count = 0
        index = start_pos
        while index <= end_pos:
            c = file.read(1)
            if c in terminators:
                count += 1
            index += 1
        return count


def main():
    comm = MPI.COMM_WORLD
    size = comm.size
    rank = comm.rank
    arg_parser = ArgumentParser(description='count sentences in a text file')
    arg_parser.add_argument('-v', dest='is_verbose', action='store_true',
                            help='verbose output for debugging')
    arg_parser.add_argument('file', metavar='FILE', help='file to parse')
    options = arg_parser.parse_args()
    file_size = os.path.getsize(options.file)
    chunck_size = file_size//size
    start_pos = chunck_size*rank
    end_pos = start_pos + chunck_size - 1 if rank + 1 < size else file_size - 1
    if options.is_verbose:
        msg = "rank {0} reading '{1}' from {2} to {3}\n"
        sys.stderr.write(msg.format(rank, options.file, start_pos, end_pos))

    prefix, new_start_pos = extract_prefix(options.file, start_pos, end_pos)
# send new_start_pos - 1 to previous, to use as new_end_pos
    if rank > 0:
        comm.isend(new_start_pos - 1, dest=rank - 1)
# receive new_new_end_pos from next
    if rank < size - 1:
        end_pos = comm.recv(source=rank + 1)
    if options.is_verbose:
        msg = "rank {0} reading '{1}' from {2} to {3}\n"
        sys.stderr.write(msg.format(rank, options.file, new_start_pos,
                                    end_pos))
    count = count_sentences(options.file, new_start_pos, end_pos)
    if options.is_verbose:
        sys.stderr.write('rank {0} counted {1}\n'.format(rank, count))
    total = comm.reduce(count, op=MPI.SUM, root=0)
    if rank == 0:
        print('sentences: {0}'.format(total))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
