#/usr/bin/env python

from mpi4py import MPI
import os
import psutil
import socket

if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    host = socket.gethostname()
    pid = os.getpid()
    msg = 'rank {0:02d} of {1:02d} as process {2:05d} on {3:s}'
    print(msg.format(rank, size, pid, host))
    process = psutil.Process()
    nr_cores = psutil.cpu_count()
    cores = process.cpu_affinity()
    msg = 'rank {0:02d} running on core(s) {1:s} of {2:d}'
    print(msg.format(rank, '.'.join(str(c) for c in cores), nr_cores))
