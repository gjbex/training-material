all: uninitialized_variable_c.exe uninitialized_variable_f90.exe \
     uninitialized_variable_correct_c.exe

warnings: uninitialized_variable.c uninitialized_variable.f90
	$(CC)  -Wmaybe-uninitialized -O3 -g -c uninitialized_variable.c
	$(FC)  -Wmaybe-uninitialized -O3 -g -c uninitialized_variable.f90

%_c.exe: %.c
	$(CC)  $(CFLAGS) -O3 -g -o $@ $<

%_f90.exe: %.f90
	$(FC)  $(FFLAGS) -O3 -g -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
