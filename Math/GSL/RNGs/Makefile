CC = gcc
CFLAGS = -O2 -g -Wall -std=c99
CPPFLAGS = $(shell pkg-config --cflags gsl)
LDFLAGS = $(shell pkg-config --libs gsl)

APPL = generate_exp_distr.exe generate_uniform_distr.exe

all: $(APPL)

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(APPL) *.o core
