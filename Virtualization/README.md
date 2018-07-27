# Virtualization
How to use Singularity, creating images/containers, and using them.

## What is it?
1. `singularity.pptx`: Powerpoint presentation on singularity.
1. `xenial_grace.def`: Singularity definition file that will install the
    `grace` application in a Xenial Xerus (16.04) Ubunto OS.
1. `xenial_openmp.def`: Singularity definition file that will install
    build essentials, git.  It will subsequently clone a GitHub repository,
    build and install an OpenMP application in it, and clean up.
1. `xenial_openmpi.def`: Singularity definition file that will install
    build essentials, Mellanox infiniband drivers, IB verbs, OpenMPI and
    git.  It will subsequently clone a GitHub repository, build and
    install an MPI application in it, and clean up.
1. `xenial_paraview.def`: Singularity definition file that will install the
    `paraview` application in a Xenial Xerus (16.04) Ubunto OS.
1. `xenial_python.def`: Singularity definition file that will install the
    latest (repository) version of Python 3, numpy, scipy, and matplotlib
    with a Qt4 backend in a Xenial Xerus (16.04) Ubunto OS.
1. `xenial_svd.def`: Singularity definition file that will install
    build essentials, Mellanox infiniband drivers, IB verbs, OpenMPI and
    git.  It will subsequently clone a GitHub repository, build and
    install an MPI application that uses Scalapack in it, and clean up.
1. `xenial_gedit.def`: Singularity recipe for `gedit` application, also
    illustrates `%setup` and `%files`.
1. `data`: some sample data files to add to the `xenial_gedit.def`
    generated image.
1. `xenial_alpino_docker.def`: Singularity image recipe file for
    building from a docker container, also illustrates
    `%labels` meta-information featrure.
