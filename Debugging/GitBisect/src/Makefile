CC = gcc
CFLAGS = -g -O2
CPPFLAGS = -MMD -MP

all: test.exe

test: all
	./test.exe

test.exe: fac.o test.o
	$(CC) $(CFLAGS) -o $@ $^

-include $(wildcard *.d)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard *.d)
	$(RM) core $(wildcard core.*)
