#!/usr/bin/env python

from argparse import ArgumentParser
import sys
from mpi4py import MPI


def send_right(comm, msg, is_verbose=False):
    rank = comm.rank
    size = comm.size
    left_msg = None
    if rank % 2 == 0:
        dest = rank + 1
        if is_verbose:
            sys.stderr.write('send from {0} to {1}\n'.format(rank, dest))
        comm.send(msg, dest=dest)
    else:
        source = rank - 1
        if is_verbose:
            sys.stderr.write('{0} recv from {1}\n'.format(rank, source))
        left_msg = comm.recv(source=source)
    if rank == 0 and is_verbose:
            sys.stderr.write('odd sending...\n')
    if rank % 2 == 1 and rank != size - 1:
        dest = rank + 1
        if is_verbose:
            sys.stderr.write('send from {0} to {1}\n'.format(rank, dest))
        comm.send(msg, dest=dest)
    elif rank % 2 == 0 and rank != 0:
        source = rank - 1
        if is_verbose:
            sys.stderr.write('{0} recv from {1}\n'.format(rank, source))
        left_msg = comm.recv(source=source)
    return left_msg


def isend_right(comm, msg, is_verbose=False):
    rank = comm.rank
    size = comm.size
    left_msg = None
    if rank < size - 1:
        comm.isend(msg, dest=rank + 1)
    if rank > 0:
        left_msg = comm.recv(source=rank - 1)
    return left_msg


def isend_left(comm, msg, is_verbose=False):
    rank = comm.rank
    size = comm.size
    right_msg = None
    if rank > 0:
        comm.isend(msg, dest=rank - 1)
    if rank < size - 1:
        right_msg = comm.recv(source=rank + 1)
    return right_msg


def main():
    comm = MPI.COMM_WORLD
    rank = comm.rank
    size = comm.size
    arg_parser = ArgumentParser(description='message exchange test')
    arg_parser.add_argument('-v', dest='is_verbose', action='store_true',
                            help='verbose output for debugging')
    options = arg_parser.parse_args()
    if options.is_verbose:
        sys.stderr.write('rank {0} out of {1}\n'.format(rank,
                                                        size))
    comm.barrier()
    if rank == 0 and options.is_verbose:
            sys.stderr.write('even sending...\n')
    comm.barrier()
    msg = 'msg to right from {0}'.format(rank)
    left_msg = isend_right(comm, msg, options.is_verbose)
    print('rank {0} received {1}'.format(rank, left_msg))
    comm.barrier()
    msg = 'msg to left from {0}'.format(rank)
    right_msg = isend_left(comm, msg, options.is_verbose)
    print('rank {0} received {1}'.format(rank, right_msg))
    comm.barrier()
    msg_in = None
    if rank == 0:
        msg_out = 'hello from 0'
        msg_in = comm.sendrecv(sendobj=msg_out, dest=1, source=1)
        print('rank {0}: {1}'.format(rank, msg_in))
    if rank == 1:
        msg_out = 'hello from 1'
        msg_in = comm.sendrecv(sendobj=msg_out, dest=0, source=0)
        print('rank {0}: {1}'.format(rank, msg_in))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
