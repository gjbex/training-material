CC = gcc
CFLAGS = -O0 -g -Wall -Wextra
LDLIBS = -lm

all: features.exe

%.exe: vectors.o %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
