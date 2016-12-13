# MpiIO
Some examples of MPI-IO.

## What is it?
1. `explicit_offsets.f90`: create a file with characters alternatingly
    written by each process using explicit offsets.
1. `views.f90`: create a file with characters alternatingly written by
    each process using individual file views and file handles.
1. `create_tasks.f90`: create a binary "task file", intended to be run
    with a single process.
1. `run_tasks.f90`: "run" the tasks defined in the binary file, using a
    shared file pointer so that each process gets an individual task
    independent of task length.
1. `tasks_mod.f90`: code to deal with the task derived data type.
1. `Makefile`: make file to build the examples.

## Note
The code illustrating shared file pointers doesn't seem to work with
Intel MPI on GPFS, it does with OpenMPI 1.10.2 though.
