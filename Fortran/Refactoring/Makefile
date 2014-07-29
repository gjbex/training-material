F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

LEGACY_OBJS = legacy.o
REFACTORED_OBJS = data_mod.o refactored.o
FIXED_OBJS = fixed.o

APPS = legacy refactored fixed

all: $(APPS)

legacy: $(LEGACY_OBJS)
	$(F90) $(FFLAGS) -o $@ $(LEGACY_OBJS) $(LDFLAGS) $(LIBS)

refactored: $(REFACTORED_OBJS)
	$(F90) $(FFLAGS) -o $@ $(REFACTORED_OBJS) $(LDFLAGS) $(LIBS)

fixed: $(FIXED_OBJS)
	$(F90) $(FFLAGS) -o $@ $(FIXED_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f *.o *.mod $(APPS)

