# Doxygen

Implementation of a box counting algorithm to determine the [Minkowski
dimension of a fractal](https://en.wikipedia.org/wiki/Minkowski%E2%80%93Bouligand_dimension).

## What is it?

1. `src/box_counting.f90`: program that computes the Minkowski dimention for a fractal that
   is represented as points in 2D unit square.
1. `docs/Doxyfile.in`: doxygen configration file.
1. `docs/mainpage.dox`: main page for the documentation.
1. `CMakeLists.txt`: CMake file to build the applications.  Illustrates how to generate
   documentation with doxygen.
