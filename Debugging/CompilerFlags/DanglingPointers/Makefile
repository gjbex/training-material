CC = gcc
CFLAGS = -g -Wall -Wextra

all: dangling.exe

debug: dangling.exe

debug: CFLAGS +=-fsanitize=address

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard core.*) core
