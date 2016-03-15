NetCDF C API examples
=====================

What is it?
-----------
Code samples of how to read and write NetCDF files using C.

1. Common files
  * `Makefile`: can be used to build the examples, note that CPPFLAGS and
    LDFLAGS will have to be set if the NetCDF library is not stored
    in standard locations
2. Writing NetCDF
  * `grid.[ch]`: defines function to create a uniform and a
    rectilinear grid, as well as functions to compute values for a given
    function on those grid points (2D and 3D).
  * `write_netcdf.c`: the program opens the NetCDF file specified on
    the command line, defines the metadata, creates the grid and the
    values on that, and writes those to the file.
