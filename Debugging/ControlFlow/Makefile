FFLAGS = -O2 -g -Wall -Wextra
CFLAGS = -O2 -g -Wall -Wextra

all: logical_order_f90.exe logical_order_c.exe init_proc_vars_f90.exe \
     unintended_global_f90.exe improper_conditionals_c.exe \
     udt_intent_out_f90.exe

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $^

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.exe *.o *.mod
	$(RM) core core.*
