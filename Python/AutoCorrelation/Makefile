CC = gcc
CFLAGS = -O2 -g
CPPFLaGS =
LDFLAGS =
LIBS = -lm

all: bin_values.exe

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLaGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLaGS) -c -o $@ $<

clean:
	rm -f *.exe *.o core
