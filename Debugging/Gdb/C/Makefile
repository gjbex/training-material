CC = gcc
CFLAGS = -g -O0
LDLIBS = -lm

all: crash.exe array_bounds.exe array_bounds_O2.exe \
	 fib_okay.exe fib_not_okay.exe hello_world.exe

array_bounds_O2.exe: array_bounds.c
	clang -O2 -Wno-unsequenced -o $@ $< $(LDLIBS)

fib_not_okay.exe: fib_not_okay.o fib_main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

fib_okay.exe: fib_okay.o fib_main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

hello_world.exe: hello_world.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $<

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
