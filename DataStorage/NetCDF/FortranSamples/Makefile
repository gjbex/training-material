F90 = gfortran
FFLAGS = -O2 -g
FPPFLAGS = -I/usr/include
LDFLAGS =
LIBS = -lnetcdff -lm

READ_NETCDF_OBJS = real_types_mod.o grid_mod.o read_netcdf.o

APPS = read_netcdf

all: $(APPS)

read_netcdf: $(READ_NETCDF_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(READ_NETCDF_OBJS) \
           $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -c $<

clean:
	rm -f *.o *.mod $(APPS)

