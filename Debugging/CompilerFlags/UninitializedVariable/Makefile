all: uninitialized_variable_c.exe uninitialized_variable_f90.exe

warnings: uninitialized_variable.c uninitialized_variable.f90
	$(CC)  -Wall -Wextra -O3 -g -c uninitialized_variable.c
	$(FC)  -Wall -Wextra -O3 -g -c uninitialized_variable.f90

%_c.exe: %.c
	$(CC)  $(CFLAGS) -O3 -g -o $@ $<

%_f90.exe: %.f90
	$(FC)  $(FFLAGS) -O3 -g -o $@ $<

clean:
	$(RM) *.o *.mod *.exe
	$(RM) core core.*
