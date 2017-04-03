# Thrust
NVIDIA Thrust is a template-based C++ library for programming GPGPUs.
See [Thrust's documentation](http://docs.nvidia.com/cuda/thrust/index.html#axzz4MyHsSHLg) for
more information.

## What is it?
1. `vectors.cu`: compares run times of SAXPY on GPU and a single core CPU.
1. `vectors_omp.cpp`: OMP implementation for a more fair comparison between CPU and GPGPU.
1. `Makefile`: make file to build the applications.
