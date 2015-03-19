HDF5 = /usr
F90 = gfortran
FFLAGS = -O2 -g
FPPFLAGS = -I$(HDF5)/include
LDFlAGS = -L$(HDF5)/lib
LIBS = -lhdf5_fortran -lm

APPS = create_h5 compute_center_of_mass append_h5

all: $(APPS)

create_h5: create_h5.o
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $< $(LDFlAGS) $(LIBS)

compute_center_of_mass: compute_center_of_mass.o
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $< $(LDFlAGS) $(LIBS)

append_h5: append_h5.o
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $< $(LDFlAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -c $<

clean:
	rm -f *.o *.mod $(APPS)

