all: array_bounds_check.exe bounds_check_impact.exe \
     bounds_check_impact_enabled.exe

warnings: array_bounds_check.f90
	$(FC) $(FLAGS) -fbounds-check -o array_bounds_check.exe  $<
	./array_bounds_check.exe

timings: bounds_check_impact_enabled.exe bounds_check_impact.exe
	time ./bounds_check_impact.exe
	time ./bounds_check_impact_enabled.exe

bounds_check_impact_enabled.exe: bounds_check_impact.f90
	$(FC) $(FLAGS) -fbounds-check -o $@  $<

%.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) *.exe *.mod *.o
	$(RM) core core.*
