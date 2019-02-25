# ExternalLibrary

Example of a project that uses an external library, and installs the executable.

## What is it?

1. `src`: source directory
  1. `minimum.cpp`: defines the main function of an application that computes
     the minimum of a quadratic function using the GSL.
     data from standard input, and writes statistics to standard output.
    1. `CMakeLists.txt`: CMake file to build and install the application.
1. `CMakeLists.txt`: CMake file to build and install the project.
1. `build.sh`: bash script to build the project.
