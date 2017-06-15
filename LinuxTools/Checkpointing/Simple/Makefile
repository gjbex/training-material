CC = gcc
CFLAGS = -g -O2

APPL = file_io.exe verify_io.exe

all: $(APPL)

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(APPL) *.o
