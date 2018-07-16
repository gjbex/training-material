CFLAGS = -O2 -g -Wall -Wextra
LDLIBS = -lm

all: bad_function_cast.exe error_handling.exe bad_function_cast_sanitized.exe

warnings:
	$(CC) $(CFLAGS) -Wbad-function-cast -c bad_function_cast.c

%_sanitized.exe: %.c
	$(CC) $(CFLAGS) -fsanitize=float-cast-overflow -o $@ $< $(LDLIBS)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
