VERSION = cpython-34m
PROFILE = ising_cython_prof.txt
override STAGE = 00
ISING_LIB=ising_cython_$(STAGE).$(VERSION).so
SETUP=setup_$(STAGE).py
override N = 150
override STEPS = 20

all: $(ISING_LIB)

$(ISING_LIB): ising_cython_$(STAGE).pyx
	python $(SETUP) build_ext --inplace

profile: $(ISING_LIB) compute_sums.py
	cp $(ISING_LIB) ising_cython.$(VERSION).so
	python -m cProfile  -s time  \
	    ./ising_sim.py --N $(N)  --steps $(STEPS)  --runs 1 \
	                   --impl cython  --seed 1234  \
        >  ising_cython_$(STAGE)_prof.txt

clean:
	python $(SETUP) clean
	rm -f ising_cython_$(STAGE).c $(ISING_LIB)
