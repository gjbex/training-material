CC = gcc
CFLAGS = -g -O0 -Wall -Wextra

all: assertions.exe assertions_no_asserts.exe

%_no_asserts.exe: %.c
	$(CC) $(CFLAGS) -D NDEBUG -o $@ $<

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard core.*) core
