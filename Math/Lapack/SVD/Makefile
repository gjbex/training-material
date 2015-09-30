HDF5_DIR = /usr
BLAS_DIR = /usr
BLACS_DIR = /usr
F90 = gfortran
MPIF90 = mpif90
FFLAGS = -O2 -g
FPPFLAGS = -I$(HDF5_DIR)/include
LIBS = -L$(HDF5_DIR)/lib -lhdf5_fortran
MATH_LIBS = -L$(BLAS_DIR) -lblas -llapack -lm
DISTR_MATH_LIBS = -L$(BLACS_DIR) -lblacsF77init-openmpi -lblacs-openmpi -lscalapack-openmpi

APPS = create_h5.exe dump_h5.exe svd.exe svd_blacs.exe \
       blacs_enlightenment.exe
OBJS = utils_mod.o matrix_mod.o

all: $(APPS)

svd.exe: $(OBJS) svd.o
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $^ $(MATH_LIBS) $(LIBS)

blacs_enlightenment.exe: blacs_enlightenment.f90
	$(MPIF90) $(FFLAGS) -o $@ $^ $(DISTR_MATH_LIBS) $(LIBS)

svd_blacs.exe: utils_mod.f90 matrix_mod.f90 svd_blacs.f90
	$(MPIF90) $(FFLAGS) $(FPPFLAGS) -o $@ $^ $(DISTR_MATH_LIBS) $(LIBS)

%.exe: $(OBJS) %.o
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $^ $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -c -o $@ $^

clean:
	rm -f $(APPS) *.o *.mod
