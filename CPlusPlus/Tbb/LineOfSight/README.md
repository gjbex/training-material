# Line of sight

This code illustrates using a parallel scan to cmopute the visibility of
points along a line.

## What is it?

1. `line_of_sight.ipynb`: Jupyter notebook to illustrate and visualize the concept.
1. `src`: directory containing the C++ source code.
   1. `terrain.h`: class definition representing a "terrain", i.e., distances and
      altitudes along a line.
   1. `terrain.cpp`: implementation of `Terrain` methods.
   1. `terrain_main.cpp`: application to create a terrain, and write it to a
      text representation.
   1. `visibility_serial.cpp`: serial implementation of the algorithm to compute
      the visibility of each point.
   1. `visibility_par.cpp`: parallel implementation of the algorithm to compute
      the visibility of each point.  This implementation uses
      `tbb:parallel_scan`.
   1. `line_of_sight_serial.cpp`: serial implementation of the algorithm to cmopute
      the actual line of sight.
   1. `CMakeLists.txt`: CMake file to build the applications.
1. `CMakeLists.txt`: CMake file to build the applications.
