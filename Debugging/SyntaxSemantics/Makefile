FFLAGS = -O2 -g -Wall -Wextra

semantic_errors: semantic_error_f90.exe

%_f90.exe: %_f90.o
	$(FC) $(FFLAGS) -o $@ $<

%_f90.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) *.exe *.o *.mod
	$(RM) core core.*
