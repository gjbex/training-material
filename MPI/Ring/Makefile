F90 = mpif90
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

all: unidirectional.exe nonblocking.exe deadlock.exe bidirectional.exe \
     sendrecv.exe cart_sendrecv.exe torus.exe

f08: nonblocking_f08.exe cart_sendrecv_f08.exe

%.exe: %.o
	$(F90) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod *.exe core
