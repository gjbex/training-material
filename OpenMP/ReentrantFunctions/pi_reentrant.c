#include <err.h>
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
 * integer value to control the size of the for-loop.  An additional optional
 * positive integer can serve as the seed for the random number generator that
 * is used to generate the seeds for the re-entrant random number generators
 * in each of the threads.
 */
int main(int argc, char *argv[]) {
    int num_threads = 1;
    long nr_tries = 10000;
    if (argc > 1)
        nr_tries = atol(argv[1]);
    unsigned int seed = 1234;
    if (argc > 2)
        seed = atoi(argv[2]);
    long nr_successes = 0;
    unsigned int *seeds;
#pragma omp parallel default(none) shared(num_threads, seed, seeds, nr_tries, nr_successes)
    {
        int thread_num = 0;
#ifdef _OPENMP
        thread_num = omp_get_thread_num();
#endif
        // a single thread will determine the number of threads
#pragma omp single
#ifdef _OPENMP
        num_threads = omp_get_num_threads();
#endif
        // printing the number of threads can be done in parallel with initializing seeds
#pragma omp sections
        {
#pragma omp section
            printf("running with %d threads\n", num_threads);
#pragma omp section
            {
                // a single thread will allocate memory for and initialize the seeds
                if (!(seeds = (unsigned int *) malloc(num_threads*sizeof(int))))
                    errx(1, "can not allocate seed array of length %d",
                            num_threads);
                srand(seed);
                for (int num = 0; num < num_threads; num++)
                    seeds[num] = rand();
            }
        }
        printf("thread %d: seed %d\n", thread_num, seeds[thread_num]);
        // all threads compute the number of successes
#pragma omp for reduction(+:nr_successes)
        for (int try_nr = 0; try_nr < nr_tries; try_nr++) {
            double x = ((double) rand_r(&(seeds[thread_num])))/((double) RAND_MAX);
            double y = ((double) rand_r(&(seeds[thread_num])))/((double) RAND_MAX);
            if (x*x + y*y < 1.0)
                nr_successes++;
        }
        // a single thread deallocates the memory
#pragma omp single
        free(seeds);
    }
    double pi = 4.0*((double) nr_successes)/((double) nr_tries);
    printf("pi = %lf\n", pi);
    return 0;
}
