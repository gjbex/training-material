VERSION = cpython-34m
ISING_LIB = ising_cython.$(VERSION).so
PROFILE = ising_cython_prof.txt
override N = 150
override STEPS = 20

all: ising_cython

ising_cython: $(ISING_LIB)

$(ISING_LIB): ising_cython.pyx
	python setup.py build_ext --inplace

profile: $(ISING_LIB) compute_sums.py
	python -m cProfile  -s time  \
	    ./ising_sim.py --N $(N)  --steps $(STEPS)  --runs 1 \
	                   --impl cython  --seed 1234  >  ising_cython_prof.txt

clean:
	python setup.py clean
	rm -f ising_cython.c $(ARRAY_SUM_LIB) $(PROFILE)
