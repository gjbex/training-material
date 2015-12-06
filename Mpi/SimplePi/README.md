# SimplePi
MPI application that computes pi using a quadrature method.  The
integration domain is partitioned among the processes.  Note that this
implementation shows how to use a number of MPI features, rather than
being intended as an efficient implementation.

## What is it?
1. `pi.c`: distributed cmoputation of pi using a quadrature method.
1. `Makefile`: make file to build the executable.
