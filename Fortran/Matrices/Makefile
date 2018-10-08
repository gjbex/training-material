FC = gfortran
FFLAGS = -O2 -g -Wall -Wextra
LDLIBS = -lm

OBJS_ALLOC = precision_defs_mod.o matrix_ops.o alloc_test.o
OBJS_CALC = precision_defs_mod.o matrix_ops.o calc_test.o
OBJS_CALC_ALLOC = precision_defs_mod.o matrix_ops.o calc_alloc_test.o
OBJS_POINTER = precision_defs_mod.o matrix_ops.o pointer_test.o
OBJS_SUBARRAY = precision_defs_mod.o matrix_ops.o subarray_test.o

APPS = alloc_test calc_test calc_alloc_test pointer_test subarray_test \
       array_init_test failed_allocate_test bounds_test

all: $(APPS)

bounds_test: bounds_test.o
	$(FC) $(FFLAGS) -o $@ $<

alloc_test: $(OBJS_ALLOC)
	$(FC) $(FFLAGS) -o $@ $(OBJS_ALLOC) $(LDFLAGS) $(LDLIBSS)

calc_test: $(OBJS_CALC)
	$(FC) $(FFLAGS) -o $@ $(OBJS_CALC) $(LDFLAGS) $(LDLIBSS)

calc_alloc_test: $(OBJS_CALC_ALLOC)
	$(FC) $(FFLAGS) -o $@ $(OBJS_CALC_ALLOC) $(LDFLAGS) $(LDLIBSS)

pointer_test: $(OBJS_POINTER)
	$(FC) $(FFLAGS) -o $@ $(OBJS_POINTER) $(LDFLAGS) $(LDLIBSS)

subarray_test: $(OBJS_SUBARRAY)
	$(FC) $(FFLAGS) -o $@ $(OBJS_SUBARRAY) $(LDFLAGS) $(LDLIBSS)

array_init_test: array_init_test.o
	$(FC) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBSS)

failed_allocate_test: failed_allocate_test.o
	$(FC) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBSS)

%.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) $(APPS) $(wildcard *.o) $(wildcard *.mod)
	$(RM) core #(wildcard core.*)
