FC = gfortran
FFLAGS = -g -O0
LDLIBS = -lm

all: matrix.exe hello_world.exe fac_init.exe array_bounds_bug.exe \
     array_bounds_no_bug.exe matrix_multiply.exe fib.exe

fac_init.exe: fac_mod.o fac_init.o
	$(FC) $(FFLAGS) -o $@ $^

matrix.exe: matrix_mod.o matrix.o
	$(FC) $(FFLAGS) -o $@ $^ $(LDLIBS)

array_bounds_bug.exe: array_bounds.o
	$(FC) -g -o $@ $<

array_bounds_no_bug.exe: array_bounds.o
	$(FC) -g -O2 -o $@ $<

hello_world.exe: hello_world.f90
	$(FC) $(FFLAGS) -fopenmp -o $@ $<

%.exe: %.o
	$(FC) $(FFLAGS) -o $@ $< $(LDLIBS)

%.o: %.f90
	$(FC) $(FFLAGS) -c $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
