#!/usr/bin/env python

import socket
from mpi4py import MPI

if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    dest = (rank + 1) % size
    source = (size + rank - 1) % size

    outgoing_msg = 'hello from rank {0} to {1}'.format(rank, dest)
    print('sending {0} to {1}'.format(outgoing_msg, dest))
    if rank % 2 == 0:
        comm.send(outgoing_msg, dest=dest, tag=11)
        incoming_msg = comm.recv(source=source, tag=11)
    else:
        incoming_msg = comm.recv(source=source, tag=11)
        comm.send(outgoing_msg, dest=dest, tag=11)

    print('{0} received {1} from {2} on {3}'.format(rank, incoming_msg,
                                                    source,
                                                    socket.gethostname()))
