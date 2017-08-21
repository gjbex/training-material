#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    const long max_count = 10000000000;
    const int padding = 16;
    long *counters;
    long sum;
    int counter_nr, nr_counters;
    struct timeval tv1, tv2;
#pragma omp parallel default(none) shared(counters, nr_counters)
    {
#pragma omp master
        {
            nr_counters = omp_get_num_threads();
        }
    }
    counters = malloc(nr_counters*sizeof(long));
    if (counters == NULL) {
        fprintf(stderr, "### error: can't allocate counters (%d)\n",
                nr_counters);
        return EXIT_FAILURE;
    }
    gettimeofday(&tv1, NULL);
#pragma omp parallel default(none) shared(counters, nr_counters)
    {
        int thread_nr = omp_get_thread_num();
        long i;
        counters[thread_nr] = 0;
        for (i = 0; i < max_count; i++)
            counters[thread_nr] += i*i + i + 5;
    }
    gettimeofday(&tv2, NULL);
    sum = 0;
    for (counter_nr = 0; counter_nr < nr_counters; counter_nr++)
        sum += counters[counter_nr];
    printf("false sharing: %.6f (%ld)\n",
           1.0e-6*(tv2.tv_usec - tv1.tv_usec) + tv2.tv_sec - tv1.tv_sec,
           sum);
    free(counters);
    counters = malloc(padding*nr_counters*sizeof(long));
    if (counters == NULL) {
        fprintf(stderr, "### error: can't allocate counters (%d)\n",
                nr_counters);
        return EXIT_FAILURE;
    }
    gettimeofday(&tv1, NULL);
#pragma omp parallel default(none) shared(counters, nr_counters)
    {
        int thread_nr = omp_get_thread_num();
        long i;
        counters[padding*thread_nr] = 0;
        for (i = 0; i < max_count; i++)
            counters[padding*thread_nr] += i*i + i + 5;
    }
    gettimeofday(&tv2, NULL);
    sum = 0;
    for (counter_nr = 0; counter_nr < nr_counters; counter_nr++)
        sum += counters[padding*counter_nr];
    printf("no false sharing: %.6f (%ld)\n",
           1.0e-6*(tv2.tv_usec - tv1.tv_usec) + tv2.tv_sec - tv1.tv_sec,
           sum);
    free(counters);
    return EXIT_SUCCESS;
}
