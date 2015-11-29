CC = gcc
CFLAGS = -O2 -g
CPPFLAGS = `pkg-config --cflags cunit`
LDFLAGS = `pkg-config --libs cunit`

all: tests

tests: tests.o fac.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f *.o *.exe tests
