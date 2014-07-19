HDF5 Fortran examples
=====================

A collection of code samples to illustrate reading and writing HDF5
files from Fortran.

What is it?
-----------
1. `create_h5.f90`: creates an HDF5 file with a `particles` group at
   root-level that contains two data sets, `mass` and `position`,
   10 x 1, and 10 x 3 respectively, type single precision real number.
2. `compute_center_of_mass.f90`: computes the center of mass of the
   particles in the file, takes a file name as command line argument.
3. `test.h5`: sample HDF5 file

How to build?
-------------
On VSC infrastructure, execute the `build.sh` script.  Elsewhere, use
the provided make file, adapting the `FPPFLAGS` and `LDFLAGS` as
necessary.

