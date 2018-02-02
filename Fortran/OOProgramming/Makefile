F90 = gfortran
FFLAGS = -O2 -g -Wall -Wextra
LIBS = -lm

TREE_TEST_OBJS = node_mod.o random_mod.o tree_test.o
ID_TREE_TEST_OBJS = node_mod.o id_node_mod.o random_mod.o id_tree_test.o
AVG_PATH_TEST_OBJS = node_mod.o random_mod.o avg_path_test.o
RAT_OBJS = rationals_mod.o rationals.o
STATS_OBJS = stats_mod.o stats.o

APPS = tree_test.exe avg_path_test.exe id_tree_test.exe rationals.exe \
       stats.exe

all: $(APPS)

tree_test.exe: $(TREE_TEST_OBJS)
	$(F90) $(FFLAGS) -o $@ $(TREE_TEST_OBJS) $(LIBS)

avg_path_test.exe: $(AVG_PATH_TEST_OBJS)
	$(F90) $(FFLAGS) -o $@ $(AVG_PATH_TEST_OBJS) $(LIBS)

id_tree_test.exe: $(ID_TREE_TEST_OBJS)
	$(F90) $(FFLAGS) -o $@ $(ID_TREE_TEST_OBJS) $(LIBS)

rationals.exe: $(RAT_OBJS)
	$(F90) $(FFLAGS) -o $@ $(RAT_OBJS) $(LIBS)

stats.exe: $(STATS_OBJS)
	$(F90) $(FFLAGS) -o $@ $(STATS_OBJS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -c $<

clean:
	rm -f *.mod *.o $(APPS)

