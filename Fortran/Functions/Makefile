FC = gfortran
FFLAGS = -O2 -g
LDFLAGS = 
LDLIBS = -lm

TIME_FUNCS_OBJS = math_func_interface.o math_func_mod.o \
                  time_func_mod.o time_funcs.o
INTERNALS_OBJS = internals_mod.o internals_test.o
QUAD_OBJS = types_mod.o quad_func_interface.o quad_mod.o quad_test.o
LINE_OBJS = types_mod.o line_mod.o line_test.o
APPS = time_funcs.exe recursion_test.exe internals_test.exe \
       vectorization_test.exe precision_test.exe \
       array_in_function_test.exe compute_stats_test.exe \
       elemental_test.exe intrinsic_test.exe initialization_test.exe \
       quad_test.exe line_test.exe root.exe quick_sort.exe

all: $(APPS)

time_funcs.exe: $(TIME_FUNCS_OBJS)
	$(FC) $(FFLAGS) -o $@ $(TIME_FUNCS_OBJS) $(LDFLAGS) $(LDLIBS)

internals_test.exe: $(INTERNALS_OBJS)
	$(FC) $(FFLAGS) -o $@ $(INTERNALS_OBJS) $(LDFLAGS) $(LDLIBS)

quad_test.exe: $(QUAD_OBJS)
	$(FC) $(FFLAGS) -o $@ $(QUAD_OBJS) $(LDFLAGS) $(LDLIBS)

line_test.exe: $(LINE_OBJS)
	$(FC) $(FFLAGS) -o $@ $(LINE_OBJS) $(LDFLAGS) $(LDLIBS)

%.exe: %.o
	$(FC) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

%.o: %.f90
	$(FC) $(FFLAGS) -c $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(APPS)
	$(RM) core $(wildcard core.*)
