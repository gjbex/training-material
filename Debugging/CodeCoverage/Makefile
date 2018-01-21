CC = gcc
CFLAGS = -g
PROF_FLAGS = -fprofile-arcs -ftest-coverage

all: fac.exe

coverage: fac.exe
	./fac.exe
	gcov funcs.c
	gcov main.c

fac.exe: main.o funcs.o
	$(CC) $(CFLAGS) $(PROF_FLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(PROF_FLAGS) -c -o $@ $<

check:
clean:
	$(RM) *.exe *.o
	$(RM) *.gcda *.gcno *.gcov
	$(RM) core core.*
