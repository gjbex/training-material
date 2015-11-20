# SparseSends
Illustrates a use case: a process receives information frmo a small number
of processes which are not known in advance.

## What is it?
1. `sparse_sends_1sided.f90`: 1-sided communication is used to determine
    the number of processes that intend to send information, the messges
    are sent using ordinary MPI_Send/MPI_Recv.
1. `sparse_sends_ibarrier.f90`: using a non-blocking barrier to indicate
    that all processes have send their messages, and that the target can
    proceed.
1. `Makefile`: make file to build the executables
