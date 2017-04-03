CC = gcc
CFLAGS = -O2 -g
CPPFLAGS = $(shell pkg-config --cflags gsl)
LDFLAGS = $(shell pkg-config --libs gsl)

all: multimin.exe

multimin.exe: multimin.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o multimin.exe
