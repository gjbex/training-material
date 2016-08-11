CC = gcc
CFLAGS = -O2 -g -Wall -std=c99
CPPFLAGS = $(shell pkg-config --cflags gsl)
LDFLAGS = $(shell pkg-config --libs gsl)

all: generate_exp_distr.exe

%.exe: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f generate_exp_distr.exe *.o core
