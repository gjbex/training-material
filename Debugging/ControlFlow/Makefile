FFLAGS = -O2 -g -Wall -Wextra
CFLAGS = -O2 -g -Wall -Wextra

APPL  = logical_order_f90.exe logical_order_c.exe init_proc_vars_f90.exe \
        unintended_global_f90.exe improper_conditionals_c.exe \
        udt_intent_out_f90.exe count_nucleotides_c.exe \
        bitwise_vs_logical_c.exe logical_control_flow_c.exe
C_APPL = $(filter %_c.exe, $(APPL))
CHECK = $(patsubst %_c.exe, %.c, $(C_APPL))

all: $(APPL)

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $^

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $^

check:
	cppcheck --quiet --enable=all --inconclusive \
             --language=c --std=c89 $(CHECK)

clean:
	$(RM) *.exe *.o *.mod
	$(RM) core core.*
