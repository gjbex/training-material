CC = gcc
CFLAGS = -O2 -g
OMP_FLAGS = -fopenmp
LDFLAGS = 
LIBS =

TARGETS = cache_lines cache_hierarchy instruction_parallelism \
          cache_associativity cache_associativity_bytes \
		  false_sharing

all: $(TARGETS)

false_sharing: false_sharing.c
	$(CC) -O0 -g $(OMP_FLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o core $(TARGETS)
