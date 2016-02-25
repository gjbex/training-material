# MatlabSamples
Examples of how to read/write HDF5 files from Matlab.

## What is it?
1. `dataset_sum.m`: Matlab function that reads a dataset from a HDF5 file
    and computes the sum of the elements.
1. `Makefile`: make file to compile the Matlab file to an executable.
1. `test.h5`: small HDF5 containing a 10 by 5 dataset of double precision
    numbers (`/values`).

## How to use?
The function `dataset_sum(file_name, dataset_name)` can be called from the
Matlab interpreter, and will return the sum of the dataset's values.

When build using the make file, i.e.,
```bash
$ make
```
the executable can be run from the command line, e.g.,
```bash
$ ./dataset_sum  test.h5  /values
````
