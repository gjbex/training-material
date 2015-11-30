MPIF90 = mpiifort
FFLAGS = -g
LDFLAGS = 
LIBS =

all: diffusion.exe 010_deadlock.exe

%.exe: %.o
	$(MPIF90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(MPIF90) $(FFLAGS) -c $<

clean:
	rm -f *.o *.exe core
