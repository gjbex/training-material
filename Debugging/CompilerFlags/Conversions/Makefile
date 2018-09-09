CC = gcc
CFLAGS = -O2 -g -Wall -Wextra
FC = gfortran
FFLAGS = -O2 -g
LDLIBS =

all: conversions.exe conversions_f90.exe

warnings:
	$(CC) $(CFLAGS) -Wconversion -c conversions.c
	$(FC) $(FFLAGS) -Wall -c conversions.f90

%_f90.exe: %.o
	$(FC) $(FFLAGS) -o $@ $<

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.mod)
	$(RM) core $(wildcard core.*)
