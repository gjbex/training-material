# ReentrantFunctions

This code illustrates the use of reentrant functions, specifically, the random
number generator.

## What is it?

1. `pi_nonreentrant.c`: application that uses `rand`.
1. `pi_reentrant.c`: application that uses `rand_r`.
1. `Makefile`: make file to build the applications.

## How to use it?

Four applications will be build.  For each of `pi_nonreentrant.c` and
`pi_reentrant.c` a version without and with OpenMP is built.  The
non-reentrant version will have terrible performance when run with
multiple threads, while the reentrant version will scale nicely.

Experiment with
```bash
$ time OMP_NUM_THREADS=1 ./pi_nonreentrant_omp.exe 100000000
```

```bash
$ time OMP_NUM_THREADS=2 ./pi_nonreentrant_omp.exe 100000000
```

```bash
$ time OMP_NUM_THREADS=1 ./pi_reentrant_omp.exe 100000000
```

```bash
$ time OMP_NUM_THREADS=2 ./pi_reentrant_omp.exe 100000000
```
