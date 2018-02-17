CC = gcc
CFLAGS = -g -O2 -Wall -Wextra

all: const_double_pointer.exe double_pointer_const.exe

errors: const_double_pointer_nok.o double_pointer_const_nok.o \
        const_double_pointer_const_nok.o

%.exe: %.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.exe *.o
	$(RM) core core.*
