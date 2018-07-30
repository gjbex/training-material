# Flatland
This is a machine learning demonstration on some of the denizens of
Flatland.

## What is it?
1. `geom_generator.py`: Python script to generate an HDF5 file with
    input and output data for the basic image recognition task. The
    HDF5 file will contain `x_values` and `y_values` datasets.  The
    x-values represent 2D input arrays, each with either a circle,
    square or equilateral triangle.   The y-values are the objexts'
    classes (0 for circle, 1 for square, 2 for triangle).
1. `data_generation.ipynb`: Jupyter notebook to illustrate the
    generation and transformation of data.
