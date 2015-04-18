F90 = gfortran
FFLAGS = -O2 -g
LDFLAGS =
LIBS = -lm

APPS = formatted_read_write_test.exe

all: $(APPS)

%.exe: %.o
	$(F90) $(FFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.mod $(APPS) text_file.txt
