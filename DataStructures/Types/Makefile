CC = gcc
CFLAGS = -g

all: types.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f types.exe U.o core
