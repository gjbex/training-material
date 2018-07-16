CC = mpicc
CFLAGS = -g -O2 -Wall -Wextra
OMPFLAGS = -fopenmp

all: 010_distributed_array.exe 020_distributed_array.exe \
     030_distributed_array.exe 040_distributed_array.exe \
     003_deadlock.exe

040_distributed_array.exe: 040_distributed_array.c
	$(CC) -g -O0 -Wall -Wextra $(OMPFLAGS) -o $@ $<

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
