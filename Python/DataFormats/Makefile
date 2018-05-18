CC = gcc
CFLAGS = -O2 -g -Wall -Wextra
LDLIBS = -lm

all: write_doubles.exe read_doubles.exe variable_length_arrays.exe \
     read_bin_records.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
