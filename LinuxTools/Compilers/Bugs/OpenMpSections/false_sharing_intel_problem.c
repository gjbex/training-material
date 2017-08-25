#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1000

int main() {
    const int nr_threads = 2;
    const int n = N;
    const int nr_runs = 20000000;
    double a[n], sum = 0.0;
    int j;
    omp_set_dynamic(0);
    omp_set_num_threads(nr_threads);

#pragma omp parallel default(none) shared(a)
    {
#pragma omp sections
        {
#pragma omp section
            {
                struct timeval tv1, tv2;
                int i, run_nr;
                int thread_nr = omp_get_thread_num();
                for (i = 0; i < n/2; i += 1)
                    a[i] = 0.0;
                gettimeofday(&tv1, NULL);
                for (run_nr = 0; run_nr < nr_runs; run_nr++)
                    for (i = 0; i < n/2 ;i += 1)
                        a[i] += i;
                gettimeofday(&tv2, NULL);
                printf("thread %d: %.6f\n", thread_nr,
                       1.0e-6*(tv2.tv_usec - tv1.tv_usec) +
                       (tv2.tv_sec - tv1.tv_sec));
            }
#pragma omp section
            {
                struct timeval tv1, tv2;
                int thread_nr = omp_get_thread_num();
                int i, run_nr;
                for (i = n/2; i < n; i += 1)
                    a[i] = 0.0;
                gettimeofday(&tv1, NULL);
                for (run_nr = 0; run_nr < nr_runs; run_nr++)
                    for (i = n/2; i < n ;i += 1)
                        a[i] += i;
                gettimeofday(&tv2, NULL);
                printf("thread %d: %.6f\n", thread_nr,
                       1.0e-6*(tv2.tv_usec - tv1.tv_usec) +
                       (tv2.tv_sec - tv1.tv_sec));
            }
        }
    }
    sum = 0.0;
    for (j = 0; j < n; j++)
        sum += a[j];
    printf("no false sharing: %.1lf\n", sum);

#pragma omp parallel default(none) shared(a)
    {
#pragma omp sections
        {
#pragma omp section
            {
                struct timeval tv1, tv2;
                int i, run_nr;
                int thread_nr = omp_get_thread_num();
                for (i = 0; i < n; i += 2)
                    a[i] = 0.0;
                gettimeofday(&tv1, NULL);
                for (run_nr = 0; run_nr < nr_runs; run_nr++)
                    for (i = 0; i < n ;i += 2)
                        a[i] += i;
                gettimeofday(&tv2, NULL);
                printf("thread %d: %.6f\n", thread_nr,
                       1.0e-6*(tv2.tv_usec - tv1.tv_usec) +
                       (tv2.tv_sec - tv1.tv_sec));
            }
#pragma omp section
            {
                struct timeval tv1, tv2;
                int i, run_nr;
                int thread_nr = omp_get_thread_num();
                for (i = 1; i < n; i += 2)
                    a[i] = 0.0;
                gettimeofday(&tv1, NULL);
                for (run_nr = 0; run_nr < nr_runs; run_nr++)
                    for (i = 1; i < n ;i += 2)
                        a[i] += i;
                gettimeofday(&tv2, NULL);
                printf("thread %d: %.6f\n", thread_nr,
                       1.0e-6*(tv2.tv_usec - tv1.tv_usec) +
                       (tv2.tv_sec - tv1.tv_sec));
            }
        }
    }
    sum = 0.0;
    for (j = 0; j < n; j++)
        sum += a[j];
    printf("false sharing: %.1lf\n", sum);

    return EXIT_SUCCESS;
}
