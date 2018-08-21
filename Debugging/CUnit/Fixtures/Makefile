CC = gcc
override CFLAGS += -O2 -g -Wall -Wextra
CPPFLAGS = $(shell pkg-config --cflags cunit)
LDFLAGS = $(shell pkg-config --libs cunit)

all: tests.exe

tests.exe: tests.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
