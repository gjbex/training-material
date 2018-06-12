CFLAGS = -g -Wall -Wextra
FFLAGS = -g -Wall
LDLIBS = -lm

all: float_equal_c.exe float_equal_f90.exe on_circle_c.exe

warnings:
	$(CC) -Wfloat-equal -c float_equal.c
	$(CC) -Wfloat-equal -c on_circle.c
	$(FC) -Wcompare-reals -c float_equal.f90

%_c.exe: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

%_f90.exe: %.f90
	$(FC) $(FFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
