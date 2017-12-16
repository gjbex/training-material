CC = gcc
CFLAGS = -O2 -g -Wall -Wextra
OMP = -fopenmp

all: multilevel_c.exe

%_c.exe: %.c
	$(CC) $(CFLAGS) $(OMP) -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) ovre core.*
