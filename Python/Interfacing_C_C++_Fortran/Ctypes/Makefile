CC = gcc
CFLAGS = -O2 -fPIC
CPPFLAGS = 
LDFLAGS =
LDLIBS = -lm

OBJS = point.o stats.o
LIB_NAME = my_stuff
LIB = ${LIB_NAME:%=lib%.so}
APPLS = point_test.exe stats_test.exe

all: $(LIB) $(APPLS) liblog_map.so

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -shared -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

point_test.exe: point_main.o $(LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ point_main.o \
          $(LDFLAGS) -L. -l$(LIB_NAME) $(LDLIBS)

stats_test.exe: stats_main.o $(LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ stats_main.o \
          $(LDFLAGS) -L. -l$(LIB_NAME) $(LDLIBS)

liblog_map.so: logistic_map.o
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.so) $(wildcard *.exe)
	$(RM) core $(wildcard core.*)
