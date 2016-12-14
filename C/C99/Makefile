CC = gcc
CFLAGS = -O2 -g -Wall -std=c99
LIBS = -lm

APPL = bool.exe complex.exe vla.exe fam.exe struct_init.exe

all: $(APPL)

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(APPL) *.o core
