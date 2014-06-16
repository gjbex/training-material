F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS = 
LIBS = -lm

TIME_FUNCS_OBJS = math_func_mod.o time_func_mod.o time_funcs.o
APPS = time_funcs

all: $(APPS)

time_funcs: $(TIME_FUNCS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(TIME_FUNCS_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f *.o *.mod $(APPS)

