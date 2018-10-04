FC = gfortran
FFLAGS = -fopenmp -O2 -g -Wall -Wextra

all: block.exe

%.exe: %.o
	$(FC) $(FFLAGS) -o $@ $<

%.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.mod) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
