CC = gcc
F90 = gfortran
CFLAGS = -O3
FFLAGS = -O3
LDFLAGS = 
LIBS = -lm

APPL = pure_c pure_fortran blas_fortran

all: $(APPL)

pure_c: pure_c_matmul.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

pure_fortran: pure_fortran_matmul.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

blas_fortran: blas_fortran.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) -lblas $(LIBS)

clean:
	rm -f *.o *.mod core $(APPL)

