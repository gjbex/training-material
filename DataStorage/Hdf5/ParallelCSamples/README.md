# HDF5 parallel I/O

## What is it?
1. `phdf5_test`: Short program to illustrate using parallel
   HDF5 capabilities.  It will simply write a 2D 8 x 5 integer dataset
   to 'my_data' in file 'test.h5'.  The processes are arranged in a
   1D topology along the x-axis, so it can only be run correctly with
   1, 2, 4, and 8 MPI processes.  Source code: `main_phdf5_test.c`.
2. `checkpoint_test`: trivial but complete example of using
   HDF5 parallel I/O for checkpointing.  The program can be started in
   two modes: 'new' and 'restart'.  In the former case, a new HDF5 file
   is created and initialized with the 2D grid information, and the
   initial values of the "field".

   ```bash
   $ mpirun -np 6 ./checkpoint_test new ckpt.h5 30 50
   ```

   The 2D field is computed on 30 x 50 grid points.  The values of the
   latter are stored in datasets 'x' and 'y' respectively, while the
   value of the field is stored in the 'field' data set. 
   When restarted, the program reads the grid information from the HDF5
   file, and initializes the field from the stored data set.  It then
   computes new field values, and stores them in the same 'field' data
   set, overwriting the original data in the HDF5 file.

   ```bash
   $ mpirun -np 4 ./checkpoint_test restart ckpt.h5
   ```

   Note that the number of processes for a restart need not be the same
   as for a previous run.  The grid is distributed on the available
   processes dynamically.
   Dource files:
  * `main_checkpoint_test.c`: main program.
  * `consts.h`: some constants used throughout the code.
  * `init.[ch]`: code to handle the command line arguments, and determine
    the grid dimensions from the HDF5 file.
  * `grid.[ch]`: code to partition the grid among processes, initialize
    the grid, and initialize the field.
  * `checkpoint.[ch]`: code that will save and read the grid and field
    to and from the HDF5 file.

## Building the program
Simply use run `build.sh` when working on a VSC cluster.

Otherwise, use the following with appropriate options
```bash
$ ./configure
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

## Running the example
Run using MPI, for `phdf5_test`, e.g.,
```bash
$ mpirun -np 4 ./phdf5_test
```

For `checkpoint_test`, e.g.,
```bash
$ mpirun -np 6 ./checkpoint_test new ckpt.h5
$ mpirun -np 4 ./checkpoint_test restart ckpt.h5
```
