#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif

/*
 * This program approximates pi by computing the area of a quarter circle and
 * compare that to a square that circumscribes it.  It generateds random x and
 * y coordinates and checks whether these are in the quarter circle or not.
 *
 * For performance tests, the application can optionally be called with an
 * integer value to control the size of the for-loop.
 */
int main(int argc, char *argv[]) {
    long nr_tries = 10000;
    if (argc > 1)
        nr_tries = atol(argv[1]);
    long nr_success = 0;
#pragma omp parallel
    {
#pragma omp single
        {
            int num_threads = 1;
#ifdef _OPENMP
            num_threads = omp_get_num_threads();
#endif
            printf("running with %d threads\n", num_threads);
        }
#pragma omp for reduction(+:nr_success)
        for (int try_nr = 0; try_nr < nr_tries; try_nr++) {
            double x = ((double) rand())/((double) RAND_MAX);
            double y = ((double) rand())/((double) RAND_MAX);
            if (x*x + y*y < 1.0)
                nr_success++;
        }
    }
    double pi = 4.0*((double) nr_success)/((double) nr_tries);
    printf("pi = %lf\n", pi);
    return 0;
}
