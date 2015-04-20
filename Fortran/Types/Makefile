F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

PART_OBJS = random_mod.o particles_mod.o particle_sim.o
RAND_TEST_OBJS = random_mod.o rand_test.o

APPS = single double particle_sim rand_test precision_test \
       select_precision_test complex_test limits_test infinity_nan_test

all: $(APPS)

single: types_test.f90
	$(F90) $(FFLAGS) -cpp -DSINGLE_PREC -o $@ $< $(LDFLAGS) $(LIBS)

double: types_test.f90
	$(F90) $(FFLAGS) -cpp -o $@ $< $(LDFLAGS) $(LIBS)

precision_test: precision_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

select_precision_test: select_precision_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

particle_sim: $(PART_OBJS)
	$(F90) $(FFLAGS) -o $@ $(PART_OBJS) $(LDFLAGS) $(LIBS)

rand_test: $(RAND_TEST_OBJS)
	$(F90) $(FFLAGS) -o $@ $(RAND_TEST_OBJS) $(LDFLAGS) $(LIBS)

complex_test: complex_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

limits_test: limits_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

infinity_nan_test: infinity_nan_test.f90
	$(F90) $(FFLAGS) -cpp -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPS) *.o *.mod
