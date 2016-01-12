CC = gcc
override CFLAGS += -g -O2 -Wall -std=c99 -fPIC
CPPFLAGS = -I${TREE_2K_DIR}/include
LDFLAGS = -L${TREE_2K_DIR}/lib
LIBS = -ltree_2k -lm

APPL = scaling
SCALING_OBJS = cl_params_aux.o cl_params.o scaling.o

all: $(APPL)

params: cl_params.h

scaling: $(SCALING_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

cl_params.h: param_defs.txt
	weave -l C -d $<

clean:
	rm -f $(SCALING_OBJS) $(APPL) core
