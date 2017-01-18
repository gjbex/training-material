# HybridPi
MPI+OpenMP application that computes pi using a quadrature method.  The
integration domain is partitioned among the processes and threads.
Note that this implementation shows how to use a number of MPI features,
rather than being intended as an efficient implementation.

MPI functions illustrated:
* `MPI_Init`
* `MPI_Comm_rank`
* `MPI_Comm_size`
* `MPI_Type_create_struct`
* `MPI_Type_commit`
* `MPI_Type_free`
* `MPI_Bcast`
* `MPI_Scatter`
* `MPI_Reduce`
* `MPI_Finalize`

OpenMP
* pragmas
  * `omp parallel`
  * `omp for`
  * `omp single`
* clauses
  * `default(none)`
  * `shared(...)`
  * `reduction(...)`
* library functions
  * `omp_get_num_threads()`
  * `omp_get_thread_num()`

## What is it?
1. `pi.c`: distributed and multithreaded computation of pi using a
    quadrature method.
1. `Makefile`: make file to build the executable.

## How to use?
Simply use the `Makefile`, i.e.,
```
$ make
```
This will produce four executables, `pi_serial.exe`, `pi_openmp.exe`,
`pi_mpi.exe`, and `mpi_hybrid.exe`.
