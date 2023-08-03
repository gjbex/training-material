#!/usr/bin/env python

from mpi4py import MPI
import numpy as np


if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    nr_points = 101
    root = 0

    send_buffer = (rank + 1)*np.linspace(0.0, 1.0, nr_points)
    recv_buffer = np.zeros(nr_points) if rank == root else None
    comm.Reduce(send_buffer, recv_buffer,
                op=MPI.SUM, root=root)
    if rank == root:
        print('reduced: {0:.4f}'.format(recv_buffer.sum()))
        check = np.zeros(nr_points)
        for i in range(size):
            check += (i + 1)*np.linspace(0.0, 1.0, nr_points)
        print('check: {0:.4f}'.format(check.sum()))
