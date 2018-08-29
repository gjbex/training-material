CC = gcc
CFLAGS = -g -O2 -Wall -Wextra

all: fac.exe fac_trapped.exe

%_trapped.exe: fac.c
	$(CC) $(CFLAGS) -ftrapv -o $@ $<

%.exe: fac.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard core.*) core
