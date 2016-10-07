MPICC = mpicc
CFLAGS = -O2 -g
CPPFLAGS = -I/usr/include/petsc
LDLIBS = -lpetsc

APPL = vec_norm.exe vec_assembly.exe

all: $(APPL)

%.exe: %.c
	$(MPICC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm -f $(APPL) *.o
