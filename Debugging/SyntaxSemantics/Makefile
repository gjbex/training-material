FFLAGS = -O2 -g -Wall -Wextra

semantic_errors: semantic_error_f90.exe

syntax_errors: syntax_error.f90
	@echo "### Note: this code contains intentional syntax errors"
	-$(FC) $(FFLAGS) -c $<

%_f90.exe: %_f90.o
	$(FC) $(FFLAGS) -o $@ $<

%_f90.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o) $(wildcard *.mod)
	$(RM) core $(wildcard core.*)
