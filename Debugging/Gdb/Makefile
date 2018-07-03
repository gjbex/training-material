CC = gcc
CFLAGS = -g
FC = gfortran
FFLAGS = -g
LDLIBS = -lm

all: crash.exe array_bounds.exe array_bounds_O2.exe \
     matrix.exe hello_world.exe fib_init.exe array_bounds_f90_bug.exe \
     array_bounds_f90_no_bug.exe fib_okay.exe fib_not_okay.exe \
     matrix_multiply.exe fib_f90.exe

array_bounds_O2.exe: array_bounds.c
	clang -O2 -Wno-unsequenced -o $@ $< $(LDLIBS)

fib_init.exe: fib_init.f90
	$(FC) $(FFLAGS) -o $@ $<

matrix.exe: matrix_mod.f90 matrix.f90
	$(FC) $(FFLAGS) -o $@ $^ $(LDLIBS)

fib_not_okay.exe: fib_not_okay.o fib_main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

fib_okay.exe: fib_okay.o fib_main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

array_bounds.exe: array_bounds.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

array_bounds_f90_bug.exe: array_bounds_f90.f90
	$(FC) -g -o $@ $<

array_bounds_f90_no_bug.exe: array_bounds_f90.f90
	$(FC) -g -O2 -o $@ $<

hello_world.exe: hello_world.f90
	$(FC) $(FFLAGS) -fopenmp -o $@ $^ $(LDLIBS)

matrix_multiply.exe: matrix_multiply.f90
	$(FC) $(FFLAGS) -o $@ $^ $(LDLIBS)

fib_f90.exe: fib.f90
	$(FC) $(FFLAGS) -o $@ $<

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
