CC = gcc
CXX = g++
CFLAGS = -O2 -fPIC
CXXFLAGS = -O2 -fPIC
CPPFLAGS = 
CPP_PYTHON = -I$(HOME)/miniconda3/envs/py36/include/python3.6m/
LDFLAGS = -L$(HOME)/miniconda3/envs/py37/lib/
LDLIBS = -lpython3.7m -lm

OBJS = cl_params.o cl_params_aux.o main.o
LOGMAP_LIB_OBJS = logistic_map_wrap.o logistic_map.o
POINT_LIB_OBJS = point.o point_wrap.o
POINT_CXX_LIB_OJBS = point_class.o point_class_wrap.o
STATS_LIB_OBJS = stats.o stats_wrap.o

all: log_test \
     liblog_map.so \
     _log_map.so _point.so _Point.so _stats.so \

_stats.so: $(STATS_LIB_OBJS)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) -o $@ $(STATS_LIB_OBJS)

_Point.so: $(POINT_CXX_LIB_OJBS)
	$(CXX) -shared $(CXXFLAGS) $(CPPFLAGS) -o $@ $(POINT_CXX_LIB_OJBS)

_point.so: $(POINT_LIB_OBJS)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) -o $@ $(POINT_LIB_OBJS)

_log_map.so: $(LOGMAP_LIB_OBJS)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) -o $@ $(LOGMAP_LIB_OBJS)

stats_wrap.o: stats_wrap.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CPP_PYTHON) -c $<

point_class_wrap.o: point_class_wrap.cxx
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(CPP_PYTHON) -c $<

point_class.o: point_class.cxx
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(CPP_PYTHON) -c $<

point_wrap.o: point_wrap.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CPP_PYTHON) -c $<

logistic_map_wrap.o: logistic_map_wrap.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CPP_PYTHON) -c $<

logistic_map_wrap.c: logistic_map.i
	swig -python $<

stats_wrap.c: stats.i
	swig -python $<

point_wrap.c: point.i
	swig -python $<

point_class_wrap.cxx: point_class.i
	swig -python -c++ $<

log_test: liblog_map.so cl_params.h $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(OBJS) \
	      $(LDFLAGS) -L. -llog_map $(LDLIBS)

liblog_map.so: logistic_map.o
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) -o $@ $<

cl_params.o: cl_params.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

cl_params_aux.o: cl_params_aux.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

cl_params.h: params.txt
	weave -l C -d $<

clean:
	$(RM) log_test $(wildcard *.so) $(wildcard *.o) $(wildcard *.pyc) \
	      logistic_map_wrap.c log_map.py \
	      point_wrap.c point.py \
	      point_class_wrap.cxx Point.py \
	      stats_wrap.c stats.py \
	      core $(wildcard core.*)

clean_weave:
	$(RM) cl_params.[ch] cl_params_aux.[ch]
