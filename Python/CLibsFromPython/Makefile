CC = gcc
CFLAGS = -O2 -fPIC
CPPFLAGS = 
LDFLAGS =
LIBS = -lm

OBJS = logistic_map.o point.o stats.o
LIB_NAME = my_stuff
LIB = ${LIB_NAME:%=lib%.so}
APPLS = log_map_test point_test stats_test

all: $(LIB) $(APPLS)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -shared -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

log_map_test: log_map_main.o $(LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ log_map_main.o \
          $(LDFLAGS) -L. -l$(LIB_NAME) $(LIBS)

point_test: point_main.o $(LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ point_main.o \
          $(LDFLAGS) -L. -l$(LIB_NAME) $(LIBS)

stats_test: stats_main.o $(LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ stats_main.o \
          $(LDFLAGS) -L. -l$(LIB_NAME) $(LIBS)

clean:
	rm -f core *.o $(LIB) $(APPLS)
