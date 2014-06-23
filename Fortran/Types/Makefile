F90 = gfortran
FFLaGS = -O2 -g -cpp
LDFLAGS =
LIBS = -lm

APPS = single double

all: $(APPS)

single: types_test.f90
	$(F90) $(FFLaGS) -DSINGLE_PREC -o $@ $< $(LDFLAGS) $(LIBS)

double: types_test.f90
	$(F90) $(FFLaGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f $(APPS) *.o *.mod
