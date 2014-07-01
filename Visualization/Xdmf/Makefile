F90 = gfortran
FFLAGS = -O2 -g
CC = gcc
CFLAGS = -O2 -g
CPPFLAGS =
LDFLAGS =
LIBS = -lm

all: creator reader text_creator h5_creator

creator: data_creator.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

text_creator: text_creator.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

h5_creator: h5_creator.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) -lhdf5 $(LIBS)

reader: data_reader.f90
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f text_creator creator reader h5_creator *.o *.mod

