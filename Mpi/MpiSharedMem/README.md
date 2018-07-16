# MpiSharedMem
Examples of shared memory programming using pure MPI.

## What is it?
1. `mpi_shared_mem.c`: simple application that created subcommunicators
    based on shared memory capabilities, and reads memory of processes
    in shared memory communicator windows.
1. `mpi_shared_mem_c.pbs`: PBS script to run the MPI shared memory
    application across multiple nodes.
1. `ring.c`: implementation of "halo exchange", but using MPI shared
    memory per node, avoiding copying.
1. `ring_c.pbs`: PBS script to run the MPI shared memory ring
    application across multiple nodes.
1. `Makefile`: make file to build the applications
