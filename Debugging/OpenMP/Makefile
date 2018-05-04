FC = gfortran
OMPFLAGS = -fopenmp
FFLAGS = -g -O0 $(OMPFLAGS) -Wall -Wextra

all: 010_pi.exe 020_pi.exe

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
