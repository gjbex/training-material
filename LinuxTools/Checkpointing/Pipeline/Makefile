CC = gcc
CFLAGS = -g -O2 -Wall

APPL = producer.exe consumer.exe verify_io.exe

all: $(APPL)

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(APPL) *.o
