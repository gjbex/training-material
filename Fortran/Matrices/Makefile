F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

OBJS_ALLOC = matrix_ops.o allocatable.o
OBJS_CALC = matrix_ops.o calculations.o

APPS = alloc_test calculations

all: $(APPS)

alloc_test: $(OBJS_ALLOC)
	$(F90) $(FFLAGS) -o $@ $(OBJS_ALLOC) $(LDFLAGS) $(LIBS)

calculations: $(OBJS_CALC)
	$(F90) $(FFLAGS) -o $@ $(OBJS_CALC) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPS) *.o *.mod
