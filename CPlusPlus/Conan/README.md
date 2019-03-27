# Conan

Conan is a C++ package manager, this directory contains example usage.

## What is it?

1. `generate_gaussian.cpp`: C++ application that generates pseudo-random numbers
   drawn from a Gaussian distribution with given mean and standard deviation. It
   relies on the `args` C++ library for command line argument handling.
1. `conanfile.txt`: Conan file describing the package requirements and build
   system.
1. `CMakeLists.txt`: CMake file to build the application.
1. `build.sh`: Bash script that builds the software, also installing dependenciesl
