F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

LEGACY_OBJS = legacy.o
REFACTORED_OBJS = data_mod.o refactored.o
REFACTORED_FUNC_OBJS = data_func_mod.o refactored_func.o
FIXED_OBJS = fixed.o

APPS = legacy refactored fixed refactored_func

all: $(APPS)

legacy: $(LEGACY_OBJS) functions.f90
	$(F90) $(FFLAGS) -o $@ $(LEGACY_OBJS) $(LDFLAGS) $(LIBS)

refactored: $(REFACTORED_OBJS) functions.f90
	$(F90) $(FFLAGS) -o $@ $(REFACTORED_OBJS) $(LDFLAGS) $(LIBS)

fixed: $(FIXED_OBJS) functions.f90
	$(F90) $(FFLAGS) -o $@ $(FIXED_OBJS) $(LDFLAGS) $(LIBS)

refactored_func: $(REFACTORED_FUNC_OBJS) functions.f90
	$(F90) $(FFLAGS) -o $@ $(REFACTORED_FUNC_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f *.o *.mod $(APPS)

