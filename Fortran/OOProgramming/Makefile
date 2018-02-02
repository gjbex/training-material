F90 = gfortran
FFLAGS = -O2 -g -Wall -Wextra
FPPFLAGS =
LDFLAGS =
LIBS = -lm

TREE_TEST_OBJS = node_mod.o random_mod.o tree_test.o
ID_TREE_TEST_OBJS = node_mod.o id_node_mod.o random_mod.o id_tree_test.o
AVG_PATH_TEST_OBJS = node_mod.o random_mod.o avg_path_test.o
RAT_OBJS = rationals_mod.o rationals.o
STATS_OBJS = stats_mod.o stats.o

APPS = tree_test.exe avg_path.exe_test id.exe_tree_test rationals.exe \
       stats.exe

all: $(APPS)

tree_test.exe: $(TREE_TEST_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(TREE_TEST_OBJS) \
           $(LDFLAGS) $(LIBS)

avg_path_test.exe: $(AVG_PATH_TEST_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(AVG_PATH_TEST_OBJS) \
           $(LDFLAGS) $(LIBS)

id_tree_test.exe: $(ID_TREE_TEST_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(ID_TREE_TEST_OBJS) \
           $(LDFLAGS) $(LIBS)

rationals.exe: $(RAT_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(RAT_OBJS) $(LDFLAGS) $(LIBS)

stats.exe: $(STATS_OBJS)
	$(F90) $(FFLAGS) $(FPPFLAGS) -o $@ $(STATS_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.f90
	$(F90) $(FFLAGS) $(FPPFLAGS) -c $<

clean:
	rm -f *.mod *.o $(APPS)

