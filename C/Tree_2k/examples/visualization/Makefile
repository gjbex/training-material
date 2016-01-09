CC = gcc
override CFLAGS += -g -O2 -Wall -std=c99
CPPFLAGS = -I${TREE_2K_DIR}/include `pkg-config --cflags gsl`
LDFLAGS = -L${TREE_2K_DIR}/lib `pkg-config --libs gsl`
LIBS = -ltree_2k

APPL = visualization
VIS_OBJS = cl_params_aux.o cl_params.o visualization.o

all: $(APPL)

params: cl_params.h

visualization: $(VIS_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

cl_params.h: param_defs.txt
	weave -l C -d $<

clean:
	rm -f $(VIS_OBJS) $(APPL) core
