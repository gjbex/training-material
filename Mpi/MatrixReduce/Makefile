MPIF90 = mpif90
FFLAGS = -O2 -g -Wall -Wextra -Wno-maybe-uninitialized
LDFLAGS =
LIBS = -lm

all: matrix_reduce.exe

%.exe: %.o
	$(MPIF90) $(FFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(MPIF90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod *.exe core
