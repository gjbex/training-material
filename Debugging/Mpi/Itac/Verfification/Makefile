CC = mpiicc
CFLAGS = -O2 -g -Wall -Wextra
CPPFLAGS = -D__PURE_INTEL_C99_HEADERS__
LDFLAGS = -L/opt/intel/itac/2018.1.017/slib -L/opt/intel/itac/2018.1.017/slib/slib_common/
LDLIBS = -lvtunwind -lVTmc -lm

all: buffer_size.exe async.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard *.prot)
	$(RM) $(wildcard core.*) core
