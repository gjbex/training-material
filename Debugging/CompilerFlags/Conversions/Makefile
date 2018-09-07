CFLAGS = -O2 -g -Wall -Wextra
LDLIBS =

all: conversions.exe

warnings:
	$(CC) $(CFLAGS) -Wconversion -c conversions.c

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
