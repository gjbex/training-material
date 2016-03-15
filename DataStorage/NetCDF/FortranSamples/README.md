NetCDF Fortran 90 API examples
==============================

What is it?
-----------
Code samples of how to read and write NetCDF files using Fortran 90.

1. Common files
  * `Makefile`: can be used to build the examples, note that FPPFLAGS and
    LDFLAGS will have to be set if the NetCDF library is not stored
    in standard locations
  * `real_types_mod.f90`: defines real kinds based on iso_fortran_env
2. Reading NetCDF
  * `grid_mod.f90`: defines two subroutines, one to read grid axis
    values, the other to read the actual values computed for those
    grid points.  Allocated arrays (1D and 3D respectively) are returned.
    Note that both functions could in fact be rolled into one by using
    Fortran's reshape function cleverly.
  * `read_netcdf.f90`: the program opens the NetCDF file specified on
    the command line, reads the grid's x-, y-, and z-cooridnates, as
    well as the computed values, and subsequently computes the maximum
    error of the stored values versus computed values.
  * `data.nc`: NetCDF file containing four variables 'x', 'y', 'z',
    'value', the first three representing the rectilinear grid
    coordinates, van value is copmputed as exp(-(x**2 + y**2 + z**2)).
    Note: this file has been produced by the C code sample
    `write_netcdf.c`.
