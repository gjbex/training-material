CC = gcc
CFLAGS = -O2 -g
OMP = -fopenmp
LIBS = -lm

APPS = allocation_serial.exe allocation_omp.exe

all: $(APPS)

%_serial.exe: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

%_omp.exe: %.c
	$(CC) $(CFLAGS) $(OMP) -o $@ $< $(LIBS)

clean:
	rm -f $(APPS) *.o
