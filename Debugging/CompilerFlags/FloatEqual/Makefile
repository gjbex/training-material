CFLAGS = -Wall -Wextra -g

all: float_equal.exe

warnings:
	$(CC) $(CFLAGS) -Wfloat-equal -c float_equal.c

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.o *.exe
	$(RM) core core.*
