FFLAGS = -O2 -g -Wall -Wextra
OMP = -fopenmp
PROF = -pg

all: julia.exe julia_prof.exe julia_omp.exe

%_omp.exe: %_omp.f90
	$(FC) $(FFLAGS) $(OMP) -o $@ $<

%_prof.exe: %.f90
	$(FC) $(FFLAGS) $(PROF) -o $@ $<

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) *.mod *.o *.exe
	$(RM) core core.*
	$(RM) julia.txt
	$(RM) gmon.out
