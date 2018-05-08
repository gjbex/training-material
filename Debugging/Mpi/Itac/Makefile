CC = mpiicc
CFLAGS = -trace -g

all: shift.exe deadlock.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
	$(RM) $(wildcard core.*) core
