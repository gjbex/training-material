FC = gfortran
FFLAGS = -g -O2
CC = gcc
CFLAGS = -g -Wall -Wextra
LDLIBS = -lm

all: array_bounds_check.exe bounds_check_impact.exe \
     bounds_check_impact_enabled.exe allocatable_bounds_check.exe \
     allocatable_bounds_check_enabled.exe array_bounds.exe

warnings: array_bounds_check.f90
	$(FC) $(FLAGS) -fbounds-check -o array_bounds_check.exe  $<
	./array_bounds_check.exe

valgrind: allocatable_bounds_check.exe
	valgrind ./$<

timings: bounds_check_impact_enabled.exe bounds_check_impact.exe
	time ./bounds_check_impact.exe
	timeble ./bounds_check_impact_enabled.exe

run: array_bounds.exe
	./$<

run_sanitized: array_bounds.exe
	./$<

run_sanitized: CFLAGS += -fsanitize=address

array_bounds.exe: array_bounds.c
	$(CC) $(CFLAGS) -o $@ $<

run_bounds: pure_array.exe
	./$<

run_bounds_sanitized: pure_array.exe
	./$<

run_bounds_sanitized: CFLAGS += -fsanitize=undefined

run_sanitized: CFLAGS += -fsanitize=address

pure_array.exe: pure_array.c
	$(CC) $(CFLAGS) -o $@ $<

%_enabled.exe: %.f90
	$(FC) $(FFLAGS) -fbounds-check -o $@  $<

confusing_names.exe: confusing_names.c
	$(CC) $(CFLAGS) -fsanitize=address -o $@ $< $(LDLIBS)

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) *.exe *.mod *.o
	$(RM) core core.*
