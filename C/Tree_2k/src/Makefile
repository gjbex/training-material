CC = gcc
override CFLAGS += -g -O2 -std=c99 -Wall -fPIC
LIBS = -lm

TREE_2K_OBJ = tree_2k_err.o node_2k.o tree_2k.o tree_2k_utils.o

all: libtree_2k.so

libtree_2k.so: $(TREE_2K_OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

docs: all
	doxygen doxygen.cfg

clean:
	rm -f *.o libtree_2k.so core
