HDF5_SERIAL_INC_DIR = /usr/include/hdf5/serial
HDF5_SERIAL_LIB_DIR = /usr/lib/x86_64-linux-gnu/hdf5/serial
BLAS_DIR = /usr
FC = gfortran
FFLAGS = -O2 -g -Wall -Wextra -fPIC
OMP = -fopenmp
SERIAL_FPPFLAGS = -I$(HDF5_SERIAL_INC_DIR)
HDF5_SERIAL_LIBS = -L$(HDF5_SERIAL_LIB_DIR)/lib -lhdf5_fortran
MATH_LIBS = -L$(BLAS_DIR) -lopenblas -llapack -lm

all: svd.exe libsvd.so multi_svd.exe

libsvd.so: utils_mod.o matrix_mod.o
	$(FC) $(FFLAGS) $(SERIAL_FPPFLAGS) -shared -o $@ $^ \
	      $(MATH_LIBS) $(HDF5_SERIAL_LIBS)

svd.exe: libsvd.so svd.o
	$(FC) $(FFLAGS) $(SERIAL_FPPFLAGS) -o $@ svd.o \
	       -L. -lsvd $(MATH_LIBS) $(HDF5_SERIAL_LIBS)

multi_svd.exe: libsvd.so multi_svd.f90
	$(FC) $(FFLAGS) $(OMP) $(SERIAL_FPPFLAGS) -o $@ multi_svd.f90 \
	       $(THREADED_MATH_LIBS) $(HDF5_SERIAL_LIBS)

%.o: %.f90
	$(FC) $(FFLAGS) $(SERIAL_FPPFLAGS) -c -o $@ $<

clean:
	$(RM) *.exe *.o *.mod *.so
