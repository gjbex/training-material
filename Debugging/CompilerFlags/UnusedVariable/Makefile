all: unused_var_c.exe

warnings: unused_var.c
	$(CC)  -Wunused-variable -O3 -g -c unused_var.c

%_c.exe: %.c
	$(CC)  $(CFLAGS) -O3 -g -o $@ $<

%_f90.exe: %.f90
	$(FC)  $(FFLAGS) -O3 -g -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.mod) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
