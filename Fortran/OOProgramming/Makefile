F90 = gfortran
FFLAGS = -O2 -g
FPPFLAGS =
LDFLAGS =
LIBS = -lm

TREE_TEST_OBJS = node_mod.o random_mod.o tree_test.o
ID_TREE_TEST_OBJS = node_mod.o id_node_mod.o random_mod.o id_tree_test.o
AVG_PATH_TEST_OBJS = node_mod.o random_mod.o avg_path_test.o

APPS = tree_test avg_path_test id_tree_test

all: $(APPS)

tree_test: $(TREE_TEST_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(TREE_TEST_OBJS) \
           $(LDFLAGS) $(LIBS)

avg_path_test: $(AVG_PATH_TEST_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(AVG_PATH_TEST_OBJS) \
           $(LDFLAGS) $(LIBS)

id_tree_test: $(ID_TREE_TEST_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(ID_TREE_TEST_OBJS) \
           $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -c $<

clean:
	rm -f *.mod *.o $(APPS)

