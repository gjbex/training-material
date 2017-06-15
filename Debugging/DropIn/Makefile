CC = gcc
CFLAGS = -g -O2 -Wall
LDFLAGS = -L.
LIBS = -lintercept

TARGETS = test_linked.exe test_not_linked.exe libintercept.so

all: $(TARGETS)

libintercept.so: intercept.c
	$(CC) $(CFLAGS) -o $@ -fPIC -shared $^

test_linked.exe: libintercept.so test.c
	$(CC) $(CFLAGS) -o $@ test.c $(LDFLAGS) $(LIBS)

test_not_linked.exe: libintercept.so test.c
	$(CC) $(CFLAGS) -o $@ test.c

clean:
	rm -f $(TARGETS) *.o
