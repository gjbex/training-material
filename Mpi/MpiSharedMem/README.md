# MpiSharedMem
Examples of shared memory programming using pure MPI.

## What is it?
1. `mpi_shared_mem.c`: simple application that created subcommunicators
    based on shared memory capabilities, and reads memory of processes
    in shared memory communicator windows.
1. `Makefile`: make file to build the applications
1. `job.pbs`: PBS script to run the MPI shared memory application across
    multiple nodes.
