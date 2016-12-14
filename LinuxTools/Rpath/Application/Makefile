CC = gcc
CFLAGS = -O2 -g
CPPFLAGS = -I../Library
LDFLAGS = -Wl,-rpath=`cd ..; pwd`/Library \
		  -L../Library
LIBS = -lhello

all: say_hello.exe

say_hello.exe: appl.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o say_hello.exe core
