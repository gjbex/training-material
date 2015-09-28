CC = gcc
CFLAGS = -O2 -g
CPPFLAGS = `pkg-config --cflags gsl`
LDFLAGS = `pkg-config --libs gsl`
LIBS = 

all: pendulum.exe

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.exe core
