CFLAGS = -O2 -g -Wall -Wextra
LDFLAGS = -lm

all: addition.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) *.exe *.o
	$(RM) core core.*
