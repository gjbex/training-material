F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS = 
LIBS = -lm

TIME_FUNCS_OBJS = math_func_interface.o math_func_mod.o \
                  time_func_mod.o time_funcs.o
INTERNALS_OBJS = internals_mod.o internals_test.o
QUAD_OBJS = types_mod.o quad_func_interface.o quad_mod.o quad_test.o
LINE_OBJS = types_mod.o line_mod.o line_test.o
APPS = time_funcs recursion_test internals_test vectorization_test \
       precision_test array_in_function_test compute_stats_test \
       elemental_test intrinsic_test initialization_test quad_test \
       line_test

all: $(APPS)

recursion_test: recursion_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

time_funcs: $(TIME_FUNCS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(TIME_FUNCS_OBJS) $(LDFLAGS) $(LIBS)

internals_test: $(INTERNALS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(INTERNALS_OBJS) $(LDFLAGS) $(LIBS)

vectorization_test: vectorization_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

precision_test: precision_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

array_in_function_test: array_in_function_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

compute_stats_test: compute_stats_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

elemental_test: elemental_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

intrinsic_test: intrinsic_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

initialization_test: initialization_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

quad_test: $(QUAD_OBJS)
	$(F90) $(FFLAGS) -o $@ $(QUAD_OBJS) $(LDFLAGS) $(LIBS)

line_test: $(LINE_OBJS)
	$(F90) $(FFLAGS) -o $@ $(LINE_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f *.o *.mod $(APPS)
