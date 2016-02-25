CC = gcc
CFLAGS = -g2
CPPFLAGS =
F90 = gfortran
FFLAGS = -g2
LDFLAGS = 
LIBS = -lm

APPS = fib.exe crash.exe array-bounds.exe matrix.exe

all: $(APPS)

matrix.exe: matrix_mod.f90 matrix.f90
	$(F90) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

array-bounds.exe: show.o array-bounds.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f *.o *.mod core $(APPS)
