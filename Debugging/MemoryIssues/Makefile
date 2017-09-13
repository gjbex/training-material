CC = gcc
CFLAGS = -O2 -g -Wall -Wextra

all: leak.exe array_bounds.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
