#!/usr/bin/env python

import time
from mpi4py import MPI

if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    dest = (rank + 1) % size
    source = (size + rank - 1) % size

    if rank == 0:
        msg = 'start in {0}'.format(rank)
        comm.send(msg, dest=dest, tag=11)
    while True:
        msg = comm.recv(source=source, tag=11)
        msg += ', now at {0}'.format(rank)
        print(msg, flush=True)
        time.sleep(1)
        comm.send(msg, dest=dest, tag=11)
