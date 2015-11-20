Mpi
===

Work in progress, for now basic examples of using the Message Passing
Interface API for distributed programming.  Examles are given for C,
Fortran (2008).

What is it?
-----------
1. `HelloWorld`: most basic MPI program to show initialization, rank, size,
    and finalization.
1. `OverlappingComputationCommunication`: illustration of overlapping
    a computation and a communcation using non-blocking communication.
1. `Pi`: sample of a hybrid MPI/OpenMP code, illustrating use of re-entrant
    `rand_r` function.
1. `Ring`: a few examples of point-to-point communication for "halo
    exchange".
1. `SparseSends`: how to receive messages from a small number of a-priory
    unknown processes.
