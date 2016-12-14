CC = gcc
CFLAGS = -O2 -g -shared -fPIC

all: libhello.so

libhello.so: hello.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o libhello.so
