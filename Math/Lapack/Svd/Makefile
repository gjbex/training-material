HDF5_DIR = /usr
BLAS_DIR = /usr
BLACS_DIR = /usr
F90 = gfortran
MPIF90 = mpif90
FFLAGS = -O2 -g
OMP = -fopenmp
FPPFLAGS = -I$(HDF5_DIR)/include
LIBS = -L$(HDF5_DIR)/lib -lhdf5_fortran
MATH_LIBS = -L$(BLAS_DIR) -lblas -llapack -lm
THREADED_MATH_LIBS = -L$(BLAS_DIR) -lblas -llapack -lm
DISTR_MATH_LIBS = -L$(BLACS_DIR) -lblacsF77init-openmpi -lblacs-openmpi -lscalapack-openmpi
HYBRID_MATH_LIBS = -L$(BLACS_DIR) -lblacsF77init-openmpi -lblacs-openmpi -lscalapack-openmpi

APPS = create_h5.exe create_test_h5.exe dump_h5.exe \
       blacs_enlightenment.exe \
       svd.exe svd_threaded.exe svd_blacs.exe svd_blacs_hybrid.exe
       
SRCS = utils_mod.f90 matrix_mod.f90

all: $(APPS)

svd.exe: $(SRCS) svd.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $^ \
	       $(MATH_LIBS) $(LIBS)

svd_threaded.exe: $(SRCS) svd.f90
	$(F90) $(FFLAGS) $(OMP) $(FPPFLAGS) -o $@ $^ \
	       $(THREADED_MATH_LIBS) $(LIBS)

svd_blacs.exe: $(SRCS) svd_blacs.f90
	$(MPIF90) $(FFLAGS) $(FPPFLAGS) -o $@ $^ \
	          $(DISTR_MATH_LIBS) $(LIBS)

svd_blacs_hybrid.exe: $(SRCS) svd_blacs.f90
	$(MPIF90) $(FFLAGS) $(OMP) $(FPPFLAGS) -o $@ $^ \
	          $(HYBRID_MATH_LIBS) $(LIBS)

blacs_enlightenment.exe: blacs_enlightenment.f90
	$(MPIF90) $(FFLAGS) -o $@ $^ $(DISTR_MATH_LIBS) $(LIBS)

%_h5.exe: $(SRCS) %_h5.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(APPS) *.o *.mod
