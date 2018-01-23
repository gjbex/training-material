#/usr/bin/env python

from mpi4py import MPI
import socket

if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    host = socket.gethostname()
    print('rank {0:02d} of {1:02d} on {2:s}'.format(rank, size, host))
