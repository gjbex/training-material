F90 = gfortran
FFLAGS = -O2 -g
FPPFLAGS =
LDFLAGS =
LIBS = -lm

TREE_TESTS_OBJS = node_mod.o tree_test.o
APPS = tree_test

all: $(APPS)

tree_test: $(TREE_TESTS_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(TREE_TESTS_OBJS) \
           $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -c $<

clean:
	rm -f *.mod *.o $(APPS)

