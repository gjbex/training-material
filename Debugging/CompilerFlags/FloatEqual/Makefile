CFLAGS = -g -Wall -Wextra
FFLAGS = -g -Wall

all: float_equal_c.exe float_equal_f90.exe

warnings:
	$(CC) -Wfloat-equal -c float_equal.c
	$(FC) -Wcompare-reals -c float_equal.f90

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
