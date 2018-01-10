FFLAGS = -O2 -g -Wall -Wextra

all: julia.exe

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) *.mod *.o *.exe
	$(RM) core core.*
	$(RM) julia.txt
