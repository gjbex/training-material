CC = gcc
CFLAGS = -g
CPPFLAGS =
F90 = gfortran
FFLAGS = -g
LDFLAGS = 
LIBS = -lm

APPS = fib.exe crash.exe array_bounds.exe matrix.exe hello_world.exe \
       fib_init.exe

all: $(APPS)

fib_init.exe: fib_init.f90
	$(F90) $(FFLAGS) -o $@ $<

matrix.exe: matrix_mod.f90 matrix.f90
	$(F90) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

array_bounds.exe: show.o array_bounds.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

hello_world.exe: hello_world.f90
	$(F90) $(FFLAGS) -fopenmp -o $@ $^ $(LDFLAGS) $(LIBS)

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f *.o *.mod core $(APPS)
