CC = gcc
CFLAGS = -O2
CPPFLAGS =
LDFLAGS =
LIBS = -lm

APPL = write_doubles read_doubles

all: $(APPL)

%: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f core *.o $(APPL)

