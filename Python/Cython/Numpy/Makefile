VERSION = cpython-34m
ARRAY_SUM_LIB = array_sum.$(VERSION).so
PROFILE = array_sums_prof.txt
override DIM = 1000
override ITER = 10

all: array_sum

array_sum: $(ARRAY_SUM_LIB)

$(ARRAY_SUM_LIB): array_sum.pyx
	python setup.py build_ext --inplace

profile: $(ARRAY_SUM_LIB) compute_sums.py
	python -m cProfile -s time \
	    ./compute_sums.py --n $(DIM) --iter $(ITER) > $(PROFILE)

clean:
	python setup.py clean
	rm -f array_sum.c $(ARRAY_SUM_LIB) $(PROFILE)
