#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void init_array(double a[], int n, int start, int stop, int incr);
void do_work(double a[], int n, int nr_runs, int start, int stop, int incr);

int main(int argc, char *argv[]) {
    const int nr_threads = 2;
    const int n = 1000;
    const int nr_runs = 20000000;
    double a[n], sum = 0.0;
    int i;
    omp_set_dynamic(0);
    omp_set_num_threads(nr_threads);

#pragma omp parallel default(none) shared(a)
    {
#pragma omp sections
        {
#pragma omp section
            {
                struct timeval tv1, tv2;
                int thread_nr = omp_get_thread_num();
                init_array(a, n, n/2, n, 1);
                gettimeofday(&tv1, NULL);
                do_work(a, n, nr_runs, n/2, n, 1);
                gettimeofday(&tv2, NULL);
                printf("thread %d: %.6f\n", thread_nr,
                       1.0e-6*(tv2.tv_usec - tv1.tv_usec) +
                       (tv2.tv_sec - tv1.tv_sec));
            }
#pragma omp section
            {
                struct timeval tv1, tv2;
                int thread_nr = omp_get_thread_num();
                init_array(a, n, 0, n/2, 1);
                gettimeofday(&tv1, NULL);
                do_work(a, n, nr_runs, 0, n/2, 1);
                gettimeofday(&tv2, NULL);
                printf("thread %d: %.6f\n", thread_nr,
                       1.0e-6*(tv2.tv_usec - tv1.tv_usec) +
                       (tv2.tv_sec - tv1.tv_sec));
            }
        }
    }
    sum = 0.0;
    for (i = 0; i < n; i++)
        sum += a[i];
    printf("no false sharing: %.1lf\n", sum);

#pragma omp parallel default(none) shared(a)
    {
#pragma omp sections
        {
#pragma omp section
            {
                struct timeval tv1, tv2;
                int thread_nr = omp_get_thread_num();
                init_array(a, n, 0, n, 2);
                gettimeofday(&tv1, NULL);
                do_work(a, n, nr_runs, 0, n, 2);
                gettimeofday(&tv2, NULL);
                printf("thread %d: %.6f\n", thread_nr,
                       1.0e-6*(tv2.tv_usec - tv1.tv_usec) +
                       (tv2.tv_sec - tv1.tv_sec));
            }
#pragma omp section
            {
                struct timeval tv1, tv2;
                int thread_nr = omp_get_thread_num();
                init_array(a, n, 1, n, 2);
                gettimeofday(&tv1, NULL);
                do_work(a, n, nr_runs, 1, n, 2);
                gettimeofday(&tv2, NULL);
                printf("thread %d: %.6f\n", thread_nr,
                       1.0e-6*(tv2.tv_usec - tv1.tv_usec) +
                       (tv2.tv_sec - tv1.tv_sec));
            }
        }
    }
    sum = 0.0;
    for (i = 0; i < n; i++)
        sum += a[i];
    printf("false sharing: %.1lf\n", sum);

    return EXIT_SUCCESS;
}

void init_array(double a[], int n, int start, int stop, int incr) {
    int i;
    for (i = start; i < stop; i += incr)
        a[i] = 0.0;
}

void do_work(double a[], int n, int nr_runs, int start, int stop, int incr) {
    int run_nr, i;
    for (run_nr = 0; run_nr < nr_runs; run_nr++)
        for (i = start; i < stop ;i += incr)
            a[i] += i;
}
