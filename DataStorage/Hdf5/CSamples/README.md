HDF5 examples
=============

What is it?
-----------
A collection of code samples to illustrate reading and writing HDF5
files from C.

* The `h5lt_*.c` examples illustrate the use of the HDF5 "lite" API for C/C++.
* The `hdf5read.c` and `hdf5write.c` illustrate the regular API for reading and
  writing data sets.
* The `hdf5extend.c` example illustrates how to extend an existing data set.
* The `hdf5partialIO.c` example illustrates using hyperslabs to read only
  part of a data set.

Building the examples
---------------------
Build by using the make file, adapting the CPPFLAGS and LDFLAGS to reflect
the location of the HDF5 header files and libraries if necessary.

Running the examples
--------------------
The `h5lt_*.c` files use the HDF5 "lite" API.
1. First generate an HDF5
   file containing a matrix in data set 'A': `./h5lt_matrix matrices.h5 A 10 8`
2. Use the same program to generate a second matrix, and store in the same
   HDF5 file as data set 'B': `./h5lt_matrix matrices.h5 B 8 6`
3. Perform a matrix multiplication of 'A' and 'B', and store as 'C':
   `./h5lt_matmul matrices.h5 A B C`. 
   The resulting matrix stored in 'C' should be a 10 x 6 data set.
4. Read the resulting matrix and display it: `./h5lt_read matrices.h5 C`

