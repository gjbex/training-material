CC = gcc
CFLAGS = -std=gnu99 -O2 -g -Wall -Wextra -Wpedantic

all: pi_nonreentrant.exe pi_nonreentrant_omp.exe \
     pi_reentrant.exe pi_reentrant_omp.exe

%_omp.exe: %.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $<

%.exe: %.c
	$(CC) $(CFLAGS) -Wno-unknown-pragmas -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) core $(wildcard core.*)
