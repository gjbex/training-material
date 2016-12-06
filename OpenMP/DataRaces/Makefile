F90 = ifort
FFLAGS = -qopenmp -O2 -g

APPL = pi1.exe pi2.exe pi3.exe pi4.exe

all: $(APPL)

%.exe: %.f90
	$(F90) $(FFLAGS) -o $@ $<

clean:
	rm -f *.o *.mod $(APPL)
