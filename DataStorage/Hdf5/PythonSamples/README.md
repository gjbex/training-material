HDF5 Python examples
====================

A collection of code samples to illustrate reading and writing HDF5
files from Python using the PyTables module.

What is it?
-----------
1. `create_table.py`: creates an HDF5 file `test.h5` that has a
    root-level group `particles` containing a data set `initial` that
    holds the particles mass, x- and y-coordinates, x- and y-component
    of its velocity as floating point numbers, and an ID as an integer
    value.
1. `add_table.py`: adds a data set `final` in the `particles` group of
    `test.h5`.
1. `add_array.py`: adds a group `fields` to `test.h5`, and inserts
    an 2D array as data set `higgs`.  The data is stored as a numpy
    array.
1. `compute_avg.py`: reads the `higgs` data set from `test.h5`, as
    numpy array, and computes the average value of all points.
1. `query_table.py`: select only the particles in the `initial` data set
    that have a velocity above a certain threshold, and print them.
1. `particle.py`: defines a class `Particle`.
1. `test.h5`: test HDF5 file.
1. `write_large_dataset.py`: script to create an HDF5 file with a large
    dataset, useful to experiment with various forms of reading the data
1. `read_large_dataset.py`: script to experiment with various read modes,
    reading an entire dataset, reading non-contiguous rows and columns
