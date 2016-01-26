#!/usr/bin/env python

from mpi4py import MPI


if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    send_buffer = [rank*size + i for i in range(size)]
    data = comm.alltoall(send_buffer)
    print('rank {0}: {1}'.format(rank, ', '.join((str(x) for x in data))))
