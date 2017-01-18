CC = gcc
MPICC = mpicc
CFLAGS = -O2 -g
OMP = -fopenmp
LIBS =

all: pi.exe

pi.exe: pi.c
	$(MPICC) $(CFLAGS) -DWITH_MPI $(OMP) -o $@ $< $(LIBS)

clean:
	rm -f *.o *.exe core
