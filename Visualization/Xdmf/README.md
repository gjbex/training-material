Xdmf
====

XDMF is an XML data format to describe scientific data.  It can store all
data, or it can use other files for "heavy data", i.e., the XDMF file
is only storing the meta-data, while binary or HDF5 files are used to
store the actual data.

XDMF can among other things be used to easily import binary or HDF5
data in ParaView.

Examples
--------
1. Binary file
  * `data_10.bin`: binary file containing values computed on each point of
     10 x 10 x 10 grid using unformatted I/O in a Fortran program.
  * `data_bin_10.xdmf`: XDMF file describing the topology and geometry
     of the structured grid, specifying the binary file that contains
     the acutal data.
  * `data_bin_10.pvsm`: ParaView state file showing import and
    of XDMF for binary data.
  * `data_creator.f90`: Fortran code to generated the data, can be called
    with a file name for the resulting binary file, and the dimensions of
    the structured grid (3 values, one for each dimension).
  * `data_creator.f90`: Fortran code to read the generated data, must be
    called with a file name for the resulting binary file, and the
    dimensions of the structured grid (3 values, one for each dimension).
    It will simply print the data to the screen for verification.
2. Time series for binary files
  * `time-series-*.bin`: binary files containing values computed on
    each point of 10 x 10 x 10 grid using unformatted I/O in a Fortran
    program.  Each binary file contains information for a single time step.
  * `data_bin_time_series.xdmf`: XDMF file describing the topology and
    geometry of the structured grid, a temporal collection defines the
    time dimension, specifying the binary file  for each time step.
  * `time_series.f90`: Fortran code to generated the data, can be called
    with a file name for the resulting binary file, the dimensions of
    the structured grid (single value, the same for each dimension), and
    the number of time steps to cmopute.
3. HDF5
  * `data.h5`: HDF5 data file that contains a 10 x 10 x 10 data set of
    single precision floating point numbers.
  * `data_h5_10.xdmf`: XDMF file describing the topology and geometry
     of the structured grid, specifying the HDF5 file that contains
     the acutal data.
  * `data_h5_10.pvsm`: ParaView state file showing import and
    of XDMF for HDF5 data.
  * `h5_creator.c`: C code to to generate an HDF5 file containing a single 
    10 x 10 x 10 data set annotated with unit information.  The program
    takes the name of the HDF5 file to write.
4. pure XDMF
  * `data.xdmf`: pure XDMF file that is self contained, i.e., the actual
    data values are present in the XML file itself.  This is mostly useful
    when experimenting with XDMF since it defeats the purpose of the
    latter.
  * `text_creator.f90`: Fortran code to procude the textual data for
    inclusion in an XDMF file.
  * `xdmf_scalar_field.py`: Python program to generate a pure XDMF file
    containing data for a scalar field on a 3D structured grid.
  * `time_series.xdmf`: pure XDMF file that is self contained, i.e., the
    actual data values are present in the XML file itself.  This is
    mostly useful when experimenting with XDMF since it defeats the
    purpose of the latter.  This represents a time series of a scalar
    field on a 3D structured grid.
  * `xdmf_time_series.py`: Python program to generate a pure XDMF file
    containing data for a time series of scalar field on a 3D structured
    grid.

Notes
-----
* The provided Fortran and C programs can be built using the included
  Makefile.  Note that CFLAGS and LDFLAGS may have to be modified to
  build the HDF5 example.
* The ParaView state files have been generated with ParaView 4.1, and may
  not work with other versions.

