F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS = 
LIBS = -lm

TIME_FUNCS_OBJS = math_func_interface.o math_func_mod.o \
                  time_func_mod.o time_funcs.o
INTERNALS_OBJS = internals_mod.o internals_test.o
QUAD_OBJS = types_mod.o quad_func_interface.o quad_mod.o quad_test.o
LINE_OBJS = types_mod.o line_mod.o line_test.o
APPS = time_funcs.exe recursion_test.exe internals_test.exe \
       vectorization_test.exe precision_test.exe \
       array_in_function_test.exe compute_stats_test.exe \
       elemental_test.exe intrinsic_test.exe initialization_test.exe \
       quad_test.exe line_test.exe root.exe

all: $(APPS)

time_funcs.exe: $(TIME_FUNCS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(TIME_FUNCS_OBJS) $(LDFLAGS) $(LIBS)

internals_test.exe: $(INTERNALS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(INTERNALS_OBJS) $(LDFLAGS) $(LIBS)

quad_test.exe: $(QUAD_OBJS)
	$(F90) $(FFLAGS) -o $@ $(QUAD_OBJS) $(LDFLAGS) $(LIBS)

line_test.exe: $(LINE_OBJS)
	$(F90) $(FFLAGS) -o $@ $(LINE_OBJS) $(LDFLAGS) $(LIBS)

%.exe: %.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f *.o *.mod $(APPS)
