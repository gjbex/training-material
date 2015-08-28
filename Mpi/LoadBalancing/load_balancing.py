#!/usr/bin/env python


def compute_bounds(size, rank, n, offset):
    chunk_size = int(n/size)
    rest = n % size
    lbound = (min(rank, size - rest)*chunk_size +
              max(0, rank - (size - rest))*(chunk_size + 1))
    ubound = lbound + (chunk_size + 1 if rank >= size - rest else chunk_size)
    return lbound + offset, ubound

if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    arg_parser = ArgumentParser(description='illustration of array '
                                            'workload balancing algorithm')
    arg_parser.add_argument('--mpi_size', type=int, required=True,
                            help='size of the MPI communicator')
    arg_parser.add_argument('--array_size', type=int, required=True,
                            help='size of array to distribute over '
                                 'processes')
    arg_parser.add_argument('--lang', choices=['C', 'Fortran'],
                            default='C', help='0 or 1 based array indexing')
    options = arg_parser.parse_args()
    if options.lang == 'C':
        offset = 0
    elif options.lang == 'Fortran':
        offset = 1
    else:
        msg = '### error: language {0} not implemented'
        sys.stderr.write(msg.format(options.lang))
        sys.exit(1)
    for rank in range(options.mpi_size):
        lbound, ubound = compute_bounds(options.mpi_size, rank,
                                        options.array_size, offset)
        print('{0:3d}: {1:10d} {2:10d}'.format(rank, lbound, ubound))
