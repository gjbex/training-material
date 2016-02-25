#!/usr/bin/env python

from argparse import ArgumentParser
from mpi4py import MPI
import sys


def compute_bounds(size, rank, n, offset):
    chunk_size = int(n/size)
    rest = n % size
    lbound = (min(rank, size - rest)*chunk_size +
              max(0, rank - (size - rest))*(chunk_size + 1))
    ubound = lbound + (chunk_size + 1
                       if rank >= size - rest
                       else chunk_size)
    return lbound + offset, ubound


def partial_pi(start_idx, end_idx, n):
    '''compute partial value of pi from start_idx to end_idx'''
    partial_sum = 0.0
    w = 1.0/n
    for i in range(start_idx, end_idx):
        x = w*(i - 0.5)
        partial_sum += 4.0/(1.0 + x**2)
    return partial_sum

if __name__ == '__main__':
    root = 0
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    arg_parser = ArgumentParser(description='compute pi')
    arg_parser.add_argument('--n', type=int, default=10000,
                            help='number of points to compute pi')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='show verbose output for debugging')
    options = arg_parser.parse_args()
    lbounds = []
    ubounds = []
    if rank == root:
        for r in range(size):
            lbound, ubound = compute_bounds(size, r, options.n, 0)
            lbounds.append(lbound)
            ubounds.append(ubound)
    n = comm.bcast(options.n, root=root)
    verbose = comm.bcast(options.verbose, root=root)
    lbound = comm.scatter(lbounds, root=root)
    ubound = comm.scatter(ubounds, root=root)
    if verbose:
        print('rank {0}: {1} -> {2}'.format(rank, lbound, ubound),
              file=sys.stderr)
    partial_sum = partial_pi(lbound, ubound, n)
    total_sum = comm.reduce(partial_sum, op=MPI.SUM, root=root)
    if rank == root:
        print('pi = {0:.12f}'.format(total_sum/n))
