CC = gcc
CFLAGS = -g -Wall -O2 --std=c99
LIBS = -lm

APPL = crash.exe

all: $(APPL)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(APPL) *.o
