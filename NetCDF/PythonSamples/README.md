NetCDF Python API examples
==========================

Code samples of how to read and write NetCDF files using the netCDF4
module for Python (not part of the standard library).

What is it?
-----------
1. `write_netcdf.py`: writes an NetCDF 3 file that has three dimensions
   x, y, and z.  The grid points are stored in variables 'x', 'y', and 'z'
   respectively, and the field is stored in a 3D variable 'field'.
   NetCDF 3 as well as NetCDF 4 can be generated since ParaView prior
   to version 4.1.x seems not to be able to deal with NetCDF 4.

