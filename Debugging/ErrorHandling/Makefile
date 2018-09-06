CC = gcc
FC = gfortran
CFLAGS = -std=c99 -g -Wall -Wextra -O2
FFLAGS = -g -Wall -Wextra -O2
LDLIBS = -lm

all: allocation_error.exe command_line_args_error.exe file_error.exe \
	 read_error.exe read_error_incorrect.exe \
	 command_line_trouble_f90.exe ieee_exceptions.exe

%_f90.exe: %.o
	$(FC) $(FFLAGS) -o $@ $<

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.f90
	$(FC) $(FFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.mod)
	$(RM) $(wildcard core.*) core
