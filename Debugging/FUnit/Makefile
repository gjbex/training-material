CC = gcc
CXX = g++
FC = gfortran
FCFLAGS = -fno-range-check -O2 -g
FSFLAG = -I
VARS = CC=$(CC) CXX=$(CXX) FC=$(FC) FCFLAGS="$(FCFLAGS)" FSFLAG=$(FSFLAG)

test:
	$(VARS) funit fac_mod

clean:
	$(RM) *.o *.mod
	$(VARS) funit --clean
