CC = gcc
CFLAGS = -fopenmp -O2 -g -Wall -Wextra

all: 010_pi.exe 020_pi.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
