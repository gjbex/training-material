CC = gcc
override CFLAGS += -g -O2 -std=c99 -Wall -fPIC
CPPFLAGS = -I..
LDFLAGS = -L..
LIBS = -ltree_2k -lcunit -lm

TESTS_OBJS = init_tests.o insert_tests.o accessor_tests.o query_tests.o \
             walk_tests.o

test: all
	./run_tests

all: test_all

test_all: $(TESTS_OBJS) test_driver.o ../libtree_2k.so
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f *.o test_all core
