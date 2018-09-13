CC = gcc
CFLAGS = -O0 -g -Wall -Wextra
LDLIBS = -lm

all: vectors.exe

vectors.exe: vectors.o vector_main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
