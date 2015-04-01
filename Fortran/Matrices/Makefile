F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

OBJS_ALLOC = matrix_ops.o alloc_test.o
OBJS_CALC = matrix_ops.o calc_test.o
OBJS_CALC_ALLOC = matrix_ops.o calc_alloc_test.o
OBJS_POINTER = matrix_ops.o pointer_test.o
OBJS_SUBARRAY = matrix_ops.o subarray_test.o

APPS = alloc_test calc_test calc_alloc_test pointer_test subarray_test

all: $(APPS)

alloc_test: $(OBJS_ALLOC)
	$(F90) $(FFLAGS) -o $@ $(OBJS_ALLOC) $(LDFLAGS) $(LIBS)

calc_test: $(OBJS_CALC)
	$(F90) $(FFLAGS) -o $@ $(OBJS_CALC) $(LDFLAGS) $(LIBS)

calc_alloc_test: $(OBJS_CALC_ALLOC)
	$(F90) $(FFLAGS) -o $@ $(OBJS_CALC_ALLOC) $(LDFLAGS) $(LIBS)

pointer_test: $(OBJS_POINTER)
	$(F90) $(FFLAGS) -o $@ $(OBJS_POINTER) $(LDFLAGS) $(LIBS)

subarray_test: $(OBJS_SUBARRAY)
	$(F90) $(FFLAGS) -o $@ $(OBJS_SUBARRAY) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPS) *.o *.mod
