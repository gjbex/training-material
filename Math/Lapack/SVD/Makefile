HDF5_DIR = /usr
F90 = gfortran
FFLAGS = -O2 -g -I$(HDF5_DIR)/include
LIBS = -L$(HDF5_DIR)/lib -lhdf5_fortran
MATH_LIBS = -lblas -llapack -lm

APPS = create_h5.exe dump_h5.exe svd.exe
OBJS = utils_mod.o matrix_mod.o

all: $(APPS)

svd.exe: $(OBJS) svd.o
	$(F90) $(FFLAGS) -o $@ $^ $(MATH_LIBS) $(LIBS)

%.exe: $(OBJS) %.o
	$(F90) $(FFLAGS) -o $@ $^ $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $^

clean:
	rm -f $(APPS) *.o *.mod
