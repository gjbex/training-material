CC = mpicc
CFLAGS = -O2 -g
FC = mpif90
FFLAGS = -O2 -g
LIBS = -lm

all: scatter_gather_c.exe scatter_gather_f90.exe

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $< $(LIBS)

clean:
	$(RM) *.o *.mod *.exe
	$(RM) core core.*
