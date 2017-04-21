CC = gcc
CFLAGS = -g
CPPFLAGS =
F90 = gfortran
FFLAGS = -g
LDFLAGS = 
LIBS = -lm

APPS = fib.exe crash.exe array_bounds.exe matrix.exe

all: $(APPS)

matrix.exe: matrix_mod.f90 matrix.f90
	$(F90) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

array_bounds.exe: show.o array_bounds.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f *.o *.mod core $(APPS)
