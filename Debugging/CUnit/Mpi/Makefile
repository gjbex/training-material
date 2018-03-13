CC = mpicc
CFLAGS = -O2 -g
CPPFLAGS = `pkg-config --cflags cunit`
LDFLAGS = `pkg-config --libs cunit`

all: tests.exe

tests.exe: tests.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
