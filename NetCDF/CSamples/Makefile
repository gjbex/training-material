CC = gcc
CFLAGS = -O2 -g
CPPFLAGS =
LDFLAGS =
LIBS = -lnetcdf -lm

WRITE_OBJS = grid.o write_netcdf.o

APPS = write_netcdf

all: $(APPS)

write_netcdf: $(WRITE_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(WRITE_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f $(WRITE_OBJS) $(APPS)

