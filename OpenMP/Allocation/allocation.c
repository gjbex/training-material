#include <err.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void init_data(int **data, int n);
void process_data(int *data, int n);
void check_data(int *data, int n, int num_threads, int count);

int main(int argc, char *argv[]) {
    const int n = 1000000, nr_steps = 1000;
    int num_threads = 1, step;
    int *data;
#pragma omp parallel
    {
#ifdef _OPENMP
#pragma omp master
        num_threads = omp_get_num_threads();
        if (n % num_threads != 0) {
            errx(EXIT_FAILURE, "number of threads should divide %d", n);
        }
#endif
        init_data(&data, n);
    }
    printf("initialized with %d threads\n", num_threads);
    printf("processing...\n");
#pragma omp parallel private(step)
    {
        {
            for (step = 0; step < nr_steps; step++) {
                process_data(data, n);
            }
        }
    }
    printf("processed with %d threads\n", num_threads);
    printf("testing...\n");
    check_data(data, n, num_threads, 1 + nr_steps);
    printf("tested\n");
    return EXIT_SUCCESS;
}

void init_data(int **data, int n) {
    int i, thread_num = 0;
#ifdef _OPENMP
    thread_num = omp_get_thread_num();
#endif
#pragma omp master
    {
        if ((*data = (int *) malloc(n*sizeof(int))) == NULL) {
            errx(EXIT_FAILURE, "can not allocate memory");
        }
    }
#pragma omp for schedule(static)
    for (i = 0; i < n; i++) {
        (*data)[i] = thread_num;
    }
}

void process_data(int *data, int n) {
    int i, thread_num = 0;
#ifdef _OPENMP
    thread_num = omp_get_thread_num();
#endif
#pragma omp for schedule(static)
    for (i = 0; i < n; i++) {
        data[i] += thread_num;
    }
}

void check_data(int *data, int n, int num_threads, int count) {
    int i, chunk_size = n/num_threads, target = -count;
    for (i = 0; i < n; i++) {
        if (i % chunk_size == 0) {
            target += count;
        }
        if (data[i] != target) {
            errx(EXIT_FAILURE, "value %d != %d for %d", data[i], target, i);
        }
    }
}
