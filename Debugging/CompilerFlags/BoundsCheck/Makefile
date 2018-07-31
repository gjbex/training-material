FC = gfortran
FFLAGS = -g -O2
CC = gcc
CFLAGS = -g -Wall -Wextra

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

%_enabled.exe: %.f90
	$(FC) $(FFLAGS) -fbounds-check -o $@  $<

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) *.exe *.mod *.o
	$(RM) core core.*
