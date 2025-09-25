#/usr/bin/env python

from argparse import ArgumentParser
from mpi4py import MPI
import os
import psutil
import socket
import time

if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    comm.Barrier()
    if rank == 0:
        arg_parser = ArgumentParser(description='check process placement '
                                                'for MPI processes')
        arg_parser.add_argument('--iters', type=int, default=1,
                                help='number of iterations')
        arg_parser.add_argument('--sleep', type=float, default=1.0,
                                help='seconds to sleep between iterations')
        options = arg_parser.parse_args()
        nr_iters = options.iters
        sleep_time = options.sleep
        print('# node-level placement')
    else:
        nr_iters = 0
        sleep_time = 0
    comm.Barrier()
    nr_iters = comm.bcast(nr_iters, root=0)
    sleep_time = comm.bcast(sleep_time, root=0)
    host = socket.gethostname()
    pid = os.getpid()
    msg = 'rank {0:02d} of {1:02d} as process {2:05d} on {3:s}'
    print(msg.format(rank, size, pid, host))
    process = psutil.Process()
    nr_cores = psutil.cpu_count()
    comm.Barrier()
    if rank == 0:
        print('# core-level placement')
    comm.Barrier()
    msg = 'rank {0:02d} running on core(s) {1:s} of {2:d}'
    for _ in range(nr_iters):
        cores = process.cpu_affinity()
        print(msg.format(rank, '.'.join(str(c) for c in cores), nr_cores))
        time.sleep(sleep_time)
