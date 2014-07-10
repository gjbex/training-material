H5_DIR = /apps/leuven/thinking/2014a/software/HDF5/1.8.12-foss-2014a-serial
CC = gcc
CFLAGS = -O2 -g
CPPFLAGS = -I$(H5_DIR)/include
LDFLAGS = -L$(H5_DIR)/lib
LIBS = -lhdf5 -lhdf5_hl -lz

APPS = hdf5read hdf5write  hdf5partialIO hdf5extend \
       h5lt_matrix h5lt_matmul h5lt_read

all: $(APPS)

hdf5write: hdf5write.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

hdf5read: hdf5read.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

hdf5partialIO: hdf5partialIO.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

hdf5extend: hdf5extend.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

h5lt_matrix: h5lt_matrix.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

h5lt_matmul: h5lt_matmul.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

h5lt_read: h5lt_read.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o $(APPS)

