#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double compute_partial_pi(long nr_tries, unsigned int *seed);

int main() {
    const long nr_tries = 1000000;
    const int nr_blocks = 10;
    int num_threads = 1;
    double nr_success = 0.0;
#pragma omp parallel default(none) shared(nr_success) shared(num_threads)
    {
        int thread_num = 0;
        unsigned int seed = 0;
#ifdef __OPENMP
        thread_num = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        seed = thread_num;
#endif
        printf("thread %d of %d\n", thread_num, num_threads);
        long partial_nr_tries = nr_tries/(num_threads*nr_blocks);
#pragma omp for reduction(+:nr_success)
        for (int i = 0; i < nr_blocks; i++)
            nr_success += compute_partial_pi(partial_nr_tries, &seed);
    }
    printf("pi = %.15lf\n", 4.0*nr_success/(num_threads*nr_blocks));
    return 0;
}

double random_number(unsigned int *seed) {
    return ((double) rand_r(seed))/RAND_MAX;
}

double compute_partial_pi(long nr_tries, unsigned int *seed) {
    double x, y, nr_success = 0.0;
    for (long i = 0; i < nr_tries; i++) {
        x = random_number(seed);
        y = random_number(seed);
        if (x*x + y*y < 1.0)
            nr_success += 1.0;
    }
    return nr_success/nr_tries;
}
