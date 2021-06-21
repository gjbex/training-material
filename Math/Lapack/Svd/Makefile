HDF5_SERIAL_INC_DIR = /usr/include/hdf5/serial
HDF5_SERIAL_LIB_DIR = /usr/lib/x86_64-linux-gnu/hdf5/serial
HDF5_MPI_INC_DIR = /usr/include/hdf5/openmpi
HDF5_MPI_LIB_DIR = /usr/lib/x86_64-linux-gnu/hdf5/openmpi
BLAS_DIR = /usr
BLACS_DIR = /usr
F90 = h5fc
MPIF90 = mpif90
FFLAGS = -O2 -g
OMP = -fopenmp
MPI_FPPFLAGS = -I$(HDF5_MPI_INC_DIR)
HDF5_SERIAL_LIBS = -L$(HDF5_SERIAL_LIB_DIR)/lib -lhdf5_fortran
HDF5_MPI_LIBS = -L$(HDF5_MPI_LIB_DIR)/lib -lhdf5_fortran
MATH_LIBS = -L$(BLAS_DIR) -lopenblas -llapack -lm
THREADED_MATH_LIBS = -L$(BLAS_DIR) -lopenblas -llapack -lm
DISTR_MATH_LIBS = -L$(BLACS_DIR) -lblacsF77init-openmpi -lblacs-openmpi -lscalapack-openmpi
HYBRID_MATH_LIBS = -L$(BLACS_DIR) -lblacsF77init-openmpi -lblacs-openmpi -lscalapack-openmpi

APPS = create_h5.exe create_test_h5.exe dump_h5.exe \
       blacs_enlightenment.exe \
       svd.exe svd_threaded.exe svd_blacs.exe svd_blacs_hybrid.exe
       
SRCS = utils_mod.f90 matrix_mod.f90

all: $(APPS)

matlab: matlab_svd

matlab_svd: matlab_svd.m
	$(MCC) $(MFLAGS) $@

svd.exe: $(SRCS) svd.f90
	$(F90) $(FFLAGS) $(SERIAL_FPPFLAGS) -o $@ $^ \
	       $(MATH_LIBS) $(HDF5_SERIAL_LIBS)

svd_threaded.exe: $(SRCS) svd.f90
	$(F90) $(FFLAGS) $(OMP) $(SERIAL_FPPFLAGS) -o $@ $^ \
	       $(THREADED_MATH_LIBS) $(HDF5_SERIAL_LIBS)

svd_blacs.exe: $(SRCS) svd_blacs.f90
	$(MPIF90) $(FFLAGS) $(MPI_FPPFLAGS) -o $@ $^ \
	          $(DISTR_MATH_LIBS) $(HDF5_MPI_LIBS)

svd_blacs_hybrid.exe: $(SRCS) svd_blacs.f90
	$(MPIF90) $(FFLAGS) $(OMP) $(MPI_FPPFLAGS) -o $@ $^ \
	          $(HYBRID_MATH_LIBS) $(HDF5_MPI_LIBS)

blacs_enlightenment.exe: blacs_enlightenment.f90
	$(MPIF90) $(FFLAGS) -o $@ $^ $(DISTR_MATH_LIBS)

%_h5.exe: $(SRCS) %_h5.f90
	$(F90) $(FFLAGS) $(SERIAL_FPPFLAGS) -o $@ $^ $(HDF5_SERIAL_LIBS)

clean:
	rm -f $(APPS) *.o *.mod \
	      matlab_svd run_matlab_svd.sh readme.txt mccExcludedFiles.log
