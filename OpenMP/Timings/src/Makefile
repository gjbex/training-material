F90 = gfortran
FFLAGS = -O2 -g
OMP = -fopenmp
LDFLAGS =
LIBS = -lm

all: implicit_do_barrier.exe

%.exe: %.o
	$(F90) $(FFLAGS) $(OMP) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) $(OMP) -c $<

clean:
	rm -f *.o *.mod *.exe core
