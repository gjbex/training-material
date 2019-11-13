CC = gcc
CFLAGS = -O2 -g -Wall -Wextra
LDLIBS = -lm

all: bin_values.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o) core
