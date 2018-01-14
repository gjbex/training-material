FFLAGS = -O2 -g -Wall -Wextra
PROF = -pg

all: julia.exe julia_prof.exe

%_prof.exe: %.f90
	$(FC) $(FFLAGS) $(PROF) -o $@ $<

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) *.mod *.o *.exe
	$(RM) core core.*
	$(RM) julia.txt
	$(RM) gmon.out
