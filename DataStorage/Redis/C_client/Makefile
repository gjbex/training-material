CC = gcc
CFLAGS = -O2 -g -Wall -std=c99
CPPFLAGS = `pkg-config --cflags hiredis`
LDFLAGS = `pkg-config --libs hiredis`

all: append.exe

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f append.exe *.o core
