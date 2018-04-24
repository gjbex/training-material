CC = mpicc
CFLAGS = -g -O2 -Wall -Wextra

all: 010_distributed_array.exe 020_distributed_array.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
