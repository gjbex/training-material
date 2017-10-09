CFLAGS = -O2 -g -Wall -Wextra

all: branch.exe

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.exe *.o
	$(RM) core core.*
