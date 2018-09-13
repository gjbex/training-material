CC = gcc
CFLAGS = -O2 -g -Wall -Wextra

all: heisenbug.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) core $(wildcard core.*)
