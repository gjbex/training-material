MPIF90 = mpif90
FFLAGS = -O2 -g

APPS = explicit_offsets.exe

all: $(APPS)

%.exe: %.f90
	$(MPIF90) $(FFLAGS) -o $@ $^

clean:
	rm -f *.o *.mod $(APPS) core
