F90 = mpif90
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

all: unidirectional.exe async.exe deadlock.exe

%.exe: %.o
	$(F90) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod *.exe core
