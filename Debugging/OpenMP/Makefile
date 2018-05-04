FC = gfortran
FFLAGS = -g -O2 -fopenmp -Wall -Wextra

all: pi.exe

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
