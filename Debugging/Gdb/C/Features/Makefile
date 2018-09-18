CC = gcc
CFLAGS = -O0 -g -Wall -Wextra
LDLIBS = -lm

all: vectors.exe infinitely_running.exe

vectors.exe: vectors.o vector_main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
