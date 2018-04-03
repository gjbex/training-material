CC = gcc
CFLAGS = -g
FC = gfortran
FFLAGS = -g
LDLIBS = -lm

all: fib.exe crash.exe array_bounds.exe matrix.exe hello_world.exe \
     fib_init.exe array_bounds_f90_bug.exe array_bounds_f90_no_bug.exe

fib_init.exe: fib_init.f90
	$(FC) $(FFLAGS) -o $@ $<

matrix.exe: matrix_mod.f90 matrix.f90
	$(FC) $(FFLAGS) -o $@ $^ $(LDLIBS)

array_bounds.exe: show.o array_bounds.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

array_bounds_f90_bug.exe: array_bounds_f90.f90
	$(FC) -g -o $@ $<

array_bounds_f90_no_bug.exe: array_bounds_f90.f90
	$(FC) -g -O2 -o $@ $<

hello_world.exe: hello_world.f90
	$(FC) $(FFLAGS) -fopenmp -o $@ $^ $(LDLIBS)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
