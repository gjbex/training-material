# Mpi
Work in progress, for now basic examples of using the Message Passing
Interface API for distributed programming.  Examles are given for C,
Fortran (2008).

## What is it?
1. `HelloWorld`: most basic MPI program to show initialization, rank, size,
    and finalization.
1. `MatrixReduce`: computing a sum of matrices in each process using
    MPI_Reduce.
1. `MpiIO`: some examples of using MPI-IO.
1. `MpiSharedMem`: illustration of MPI shared memory programming.
1. `mpi.pptx`: a very basic and gentle introduction to MPI from a
    C programmer's perspective.
1. `MultiApp`: illustrations of how to use MPI communication between
    applications.
1. `OverlappingComputationCommunication`: illustration of overlapping
    a computation and a communcation using non-blocking communication.
1. `Pi`: sample of a hybrid MPI/OpenMP code, illustrating use of re-entrant
    `rand_r` function.
1. `Ring`: a few examples of point-to-point communication for "halo
    exchange".
1. `ScatterGather`: simple illustration of using the scatter/gather
    subroutines of MPI.
1. `SimplePi`: the implementation to compute pi using quadrature
    mentioned in the `mpi.pptx` slides.
1. `SparseSends`: how to receive messages from a small number of a-priory
    unknown processes.
1. `Communicators`: sample code relating to communicators and groups.
