#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE (64L * 1024L * 1024L * 32L)

int main(int argc, char *argv[]) {
    struct timeval tv1, tv2;
    int *a;
    long i, k;
    long stride[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                     16, 32, 64, 128, 256, 512, 1024};
    a = (int *) calloc(SIZE, sizeof(int));
    if (!a)
        errx(EXIT_FAILURE, "can not allocate array");
    printf("stride,time\n");
    for (k = 0; k < 22; k++) {
        gettimeofday(&tv1, NULL);
        for (i = 0; i < SIZE; i += stride[k])
            a[i] += 3;
        gettimeofday(&tv2, NULL);
        printf("%ld,%.6f\n", stride[k],
               ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
               ((double) tv2.tv_sec - tv1.tv_sec));
    }
    free(a);
    return EXIT_SUCCESS;
}

