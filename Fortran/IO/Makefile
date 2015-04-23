F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm
CC = gcc
CFLAGS = -O2 -g

APPS = formatted_read_write_test.exe unformatted_read_write_test.exe \
       stream_read_write_test.exe read_test.exe write_stream_test.exe \
       read_stream_test.exe read_stream.exe inquire_test.exe \
       append_test.exe

all: $(APPS)

read_test.exe: read_test.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

read_stream.exe: read_stream.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.exe: %.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod $(APPS) \
          text_file.txt bin_file.dat stream_file.dat array_file.dat \
          data.txt
