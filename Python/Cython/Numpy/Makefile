VERSION = cpython-34m
ARRAY_SUM_LIB = array_sum.$(VERSION).so
ARRAY_INIT_LIB = array_init.$(VERSION).so
PROFILE = array_sums_prof.txt
override DIM = 1000
override ITER = 10

all: $(ARRAY_SUM_LIB) $(ARRAY_INIT_LIB)

$(ARRAY_SUM_LIB): array_sum.pyx
	python setup.py build_ext --inplace

$(ARRAY_INIT_LIB): array_init.pyx
	python setup.py build_ext --inplace

profile: $(ARRAY_SUM_LIB) compute_sums.py
	python -m cProfile -s time \
	    ./compute_sums.py --n $(DIM) --iter $(ITER) > $(PROFILE)

clean:
	python setup.py clean
	rm -f array_sum.c $(ARRAY_SUM_LIB) $(PROFILE) \
	rm -f array_init.c $(ARRAY_INIT_LIB)
