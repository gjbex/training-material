FC = gfortran
FFLAGS = -fopenmp -O0 -g

all: pi1.exe pi2.exe pi3.exe pi4.exe pi5.exe pi_classic.exe

%.exe: %.o
	$(FC) $(FFLAGS) -o $@ $<

%.o: %.f90
	$(FC) $(FFLAGS) -o $@ -c $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
