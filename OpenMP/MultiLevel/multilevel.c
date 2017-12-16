#include <err.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int size = 10, i;
    double *a, *b;
    if (argc > 1)
        size = atoi(argv[1]);
#pragma omp parallel default(none) shared(size, a, b) \
                     num_threads(2) proc_bind(spread)
    {
        printf("thread %d out of %d\n", omp_get_thread_num(),
               omp_get_num_threads());
#pragma omp sections
        {
#pragma omp section
            {
                /* initialize a */
                int i;
                printf("thread %d initializing a\n", omp_get_thread_num());
                a = (double *) malloc(size*sizeof(double));
                if (a == NULL)
                    errx(EXIT_FAILURE, "can't allocate a, size %d\n", size);
#pragma omp parallel for schedule(static) proc_bind(close)
                for (i = 0; i < size; i++)
                    a[i] = (double) omp_get_thread_num();
                sleep(1);
            }
 #pragma omp section
            /* initialize b */
            {
                int i;
                printf("thread %d initializing b\n", omp_get_thread_num());
                b = (double *) malloc(size*sizeof(double));
                if (b == NULL)
                    errx(EXIT_FAILURE, "can't allocate b, size %d\n", size);
#pragma omp parallel for schedule(static) proc_bind(close)
                for (i = 0; i < size; i++)
                    b[i] = (double) 100*omp_get_thread_num();
                sleep(1);
            }
        }
    }
    printf("a -> 0:%.1lf", a[0]);
    for (i = 1; i < size; i++)
        if (a[i] != a[i - 1])
            printf(" %d:%.1lf", i, a[i]);
    printf("\n");
    printf("b -> 0:%.1lf", b[0]);
    for (i = 1; i < size; i++)
        if (b[i] != b[i - 1])
            printf(" %d:%.1lf", i, b[i]);
    printf("\n");
    return EXIT_SUCCESS;
}
