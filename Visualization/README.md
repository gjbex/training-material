Visualization
=============

These files (data, scripts, ParaView state files) are used during an
information session (live demo) on visualization of scientific data
using ParaView.

CSV
---
Given the formats simplicity, it can be used as a first start for data
sets tat are not too large or complex.

NetCDF
------
Unlike for binary or HDF5 files, ParaView has better support for this
format out of the box.

Xdmf
----
XDMF is an XML exchange format for scientific data that can be used to
describe data that is stored in binary or HDF5 format so that it can
easily be imported in ParaView.

Synthetic
---------
Python script to generate datasets for visualization with, e.g.,
Paraview.  Particle, scalar field and vector field data can be geenrated
in an HDF5 file, with an XDMF for metadata.
