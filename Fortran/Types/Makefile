F90 = gfortran
FFLaGS = -O2 -g -cpp
LDFLAGS =
LIBS = -lm

PaRT_OBJS = particles_mod.o particle_sim.o
APPS = single double particle_sim

all: $(APPS)

single: types_test.f90
	$(F90) $(FFLaGS) -DSINGLE_PREC -o $@ $< $(LDFLAGS) $(LIBS)

double: types_test.f90
	$(F90) $(FFLaGS) -o $@ $< $(LDFLAGS) $(LIBS)

particle_sim: $(PaRT_OBJS)
	$(F90) $(FFLaGS) -o $@ $(PaRT_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLaGS) -c $<

clean:
	rm -f $(APPS) *.o *.mod
