F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS = 
LIBS = -lm

TIME_FUNCS_OBJS = math_func_interface.o math_func_mod.o \
                  time_func_mod.o time_funcs.o
INTERNALS_OBJS = internals_mod.o internals_test.o
APPS = time_funcs recursion_test internals_test vectorization_test \
       precision_test

all: $(APPS)

recursion_test: recursion_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

time_funcs: $(TIME_FUNCS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(TIME_FUNCS_OBJS) $(LDFLAGS) $(LIBS)

internals_test: $(INTERNALS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(INTERNALS_OBJS) $(LDFLAGS) $(LIBS)

vectorization_test: vectorization_test.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

precision_test: precision_test.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f *.o *.mod $(APPS)

