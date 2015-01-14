#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_SIZE (64 * 1024 * 1024)
#define SIZE_STEP (1024 * 1024)
#define MAX_STEPS 5000
#define ITERS (32 * 1024 * 1024)

int main(int argc, char *argv[]) {
    struct timeval tv1, tv2;
    double *a;
    int arr_size, step;
    a = (double *) calloc(MAX_SIZE, sizeof(double));
    if (!a)
        errx(EXIT_FAILURE, "can not allocate array");
    printf("array size,step,time\n");
    for (arr_size = SIZE_STEP; arr_size <= MAX_SIZE;
         arr_size += SIZE_STEP) {
        for (step = 1; step < MAX_STEPS; step++) {
            int pos = 0, i;
            gettimeofday(&tv1, NULL);
            for (i = 0; i < ITERS; i++) {
                a[pos] += 1.2;
                pos += step;
                if (pos >= arr_size) pos = 0;
            }
            gettimeofday(&tv2, NULL);
            printf("%d,%d,%.6f\n", arr_size, step,
                   ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
                   ((double) tv2.tv_sec - tv1.tv_sec));
        }
    }
    free(a);
    return EXIT_SUCCESS;
}

