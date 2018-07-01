CFLAGS = -O2 -g -Wall -Wextra
LDLIBS = -lm

all: bad_function_cast.exe error_handling.exe

warnings:
	$(CC) $(CFLAGS) -Wbad-function-cast -c bad_function_cast.c

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
