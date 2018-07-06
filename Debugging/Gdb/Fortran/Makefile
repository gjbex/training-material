FC = gfortran
FFLAGS = -g -O0
LDLIBS = -lm

all: matrix.exe hello_world.exe fac_init.exe array_bounds_bug.exe \
     array_bounds_no_bug.exe matrix_multiply.exe fib.exe

fac_init.exe: fac_mod.f90 fac_init.f90
	$(FC) $(FFLAGS) -o $@ $^

matrix.exe: matrix_mod.f90 matrix.f90
	$(FC) $(FFLAGS) -o $@ $^ $(LDLIBS)

array_bounds_bug.exe: array_bounds.f90
	$(FC) -g -o $@ $<

array_bounds_no_bug.exe: array_bounds.f90
	$(FC) -g -O2 -o $@ $<

hello_world.exe: hello_world.f90
	$(FC) $(FFLAGS) -fopenmp -o $@ $^ $(LDLIBS)

matrix_multiply.exe: matrix_multiply.f90
	$(FC) $(FFLAGS) -o $@ $^ $(LDLIBS)

fib.exe: fib.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
