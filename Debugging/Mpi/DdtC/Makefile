CC = mpicc
CFLAGS = -g -O2 -Wall -Wextra

all: distributed_array.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe
	$(RM) $(wildcard core.*) core
