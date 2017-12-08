CC = mpicc
CFLAGS = -O2 -g -Wall -Wextra
F90 = mpif90
FFLAGS = -O2 -g

APPS = load_balancing_c.exe load_balancing_f90.exe

all: $(APPS)

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

%_f90.exe: %.f90
	$(F90) $(FFLAGS) -o $@ $<

clean:
	rm -f *.o *.mod $(APPS)
