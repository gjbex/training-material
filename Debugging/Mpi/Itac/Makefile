CC = mpiicc
CFLAGS = -profile=vtfs -g
FC = mpiifort
FFLAGS = -g

all: shift_c.exe deadlock_c.exe deadlock_f90.exe

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard *.stf) $(wildcard *.stf.*) $(wildcard *.prot)
	$(RM) $(wildcard core.*) core
