HDF5 parallel I/O
=================

What is it?
-----------
Short program to illustrate using parallel HDF5 capabilities.

Building the program
--------------------
Simply use run `build.sh` when working on a VSC cluster.

Otherwise, use the following with appropriate options
```
$ configur
$ make
$ make install
```

Note:
* The executable will be installed on the GPFS parallel file system since 
  it requires a parallel file system to run.  It will be installed in
  `${VSC_SCRATCH/phdf5`.
* The parallel version of the HDF5 library is required, hence don't
  forget to load the appropriate module (HDF5/1.8.12-intel-2014a-gpfs on
  VSC clusters).

Running the example
-------------------
Run using MPI, e.g.,
```
$ mpirun -np 4 ./phdf5_test
```

