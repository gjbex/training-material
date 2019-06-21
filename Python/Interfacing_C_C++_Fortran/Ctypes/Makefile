CC = gcc
CFLAGS = -O2 -fPIC
CPPFLAGS = 
CPP_PYTHON = -I$(HOME)/miniconda3/envs/py36/include/python3.6m/
LDFLAGS = -L$(HOME)/miniconda3/envs/py37/lib/
LDLIBS = -lpython3.7m -lm

LOGMAP_LIB_OBJS = logistic_map_wrap.o logistic_map.o
POINT_LIB_OBJS = point.o point_wrap.o
POINT_CXX_LIB_OJBS = point_class.o point_class_wrap.o
STATS_LIB_OBJS = stats.o stats_wrap.o

all: liblog_map.so

liblog_map.so: logistic_map.o
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.so) $(wildcard *.o) $(wildcard *.pyc) \
	      core $(wildcard core.*)
