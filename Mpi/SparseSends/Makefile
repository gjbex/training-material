F90 = mpif90
FFLAGS = -O2 -g
LDFLAGS =
LIBS =

all: sparse_sends_1sided.exe sparse_sends_ibarrier.exe \
     sparse_sends_reduce.exe

%.exe: %.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.exe *.o *.mod
