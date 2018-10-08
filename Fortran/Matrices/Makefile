F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

OBJS_ALLOC = precision_defs_mod.o matrix_ops.o alloc_test.o
OBJS_CALC = precision_defs_mod.o matrix_ops.o calc_test.o
OBJS_CALC_ALLOC = precision_defs_mod.o matrix_ops.o calc_alloc_test.o
OBJS_POINTER = precision_defs_mod.o matrix_ops.o pointer_test.o
OBJS_SUBARRAY = precision_defs_mod.o matrix_ops.o subarray_test.o

APPS = alloc_test calc_test calc_alloc_test pointer_test subarray_test \
       array_init_test failed_allocate_test bounds_test

all: $(APPS)

bounds_test: bounds_test.f90
	$(F90) $(FFLAGS) -o $@ $<

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

array_init_test: array_init_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

failed_allocate_test: failed_allocate_test.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c $<

clean:
	rm -f $(APPS) *.o *.mod
