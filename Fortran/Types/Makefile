F90 = gfortran
FFLAGS = -O2 -g -cpp
LDFLAGS =
LIBS = -lm

PART_OBJS = particles_mod.o particle_sim.o
RAND_TEST_OBJS = random_mod.o rand_test.o

APPS = single double particle_sim rand_test

all: $(APPS)

single: types_test.f90
	$(F90) $(FFLAGS) -DSINGLE_PREC -o $@ $< $(LDFLAGS) $(LIBS)

double: types_test.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

particle_sim: $(PART_OBJS)
	$(F90) $(FFLAGS) -o $@ $(PART_OBJS) $(LDFLAGS) $(LIBS)

rand_test: $(RAND_TEST_OBJS)
	$(F90) $(FFLAGS) -o $@ $(RAND_TEST_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPS) *.o *.mod
