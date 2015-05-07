Synthetic
=========

Script `create_dataset_.py` generates an HDF5 dataset that can contain
particle data, scalar field and vector field data.  The sizes of the
data can be adjusted.  This script is intended to generate precisely
controlled datasets for benchmarking of visualization software such as
Paraview.

What is is?
-----------
1. `create_dataset.py`: script to generate the dataset and the
    corresponding XDMF file that contains the metadata.  The following
    options control which data is generated:
  * `--particle_data`: include particle data; particles have a position
    in 3D space, a mass and a velocity.  The number of particles can be
    selected using the `--particles` option.
  * `--scalar_field_data`: include a scalar field (will also ensure grid
    data is saved, the resolution of that 3D grid is controlled using the
    `--points` option).
  * `--scalar_field_data`: include a scalar field (will also ensure grid
    data is saved, the resolution of that 3D grid is controlled using the
    `--points` option).
1. `xdmf.py`: class that implements an XDMF constructor.
