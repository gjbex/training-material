CC = gcc
CFLAGS = -O2
OMP_FLAGS = -fopenmp
LDFLAGS = 
LIBS =

TARGETS = cache_lines cache_hierarchy instruction_parallelism \
          cache_associativity false_sharing

all: $(TARGETS)

false_sharing: false_sharing.c
	$(CC) $(CFLAGS) $(OMP_FLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o core $(TARGETS)
