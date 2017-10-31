all: bad_function_cast.exe

warnings:
	$(CC) $(CFLAGS) -Wbad-function-cast -c bad_function_cast.c

bad_function_cast.exe: bad_function_cast.c
	$(CC) $(CFLAGS) -Wall -Wextra -o $@ $< -lm

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
