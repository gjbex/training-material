CC = gcc
CFLAGS = -O2 -g
CPPFLAGS =
LDFLAGS =
LIBS = -lnetcdf -lm

APPS = write_netcdf

all: $(APPS)

write_netcdf: write_netcdf.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o $(APPS)

