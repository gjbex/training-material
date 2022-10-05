CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -Wpedantic

all: sum_all.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe)
