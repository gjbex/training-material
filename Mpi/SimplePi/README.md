# SimplePi
MPI application that computes pi using a quadrature method.  The
integration domain is partitioned among the processes.  Note that this
implementation shows how to use a number of MPI features, rather than
being intended as an efficient implementation.

MPI functions illustrated:
* `MPI_Init`
* `MPI_Comm_rank`
* `MPI_Comm_size`
* `MPI_Type_struct`
* `MPI_Type_commit`
* `MPI_Bcast`
* `MPI_Scatter`
* `MPI_Reduce`
* `MPI_Finalize`

## What is it?
1. `pi.c`: distributed cmoputation of pi using a quadrature method.
1. `Makefile`: make file to build the executable.
