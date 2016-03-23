#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE (64L * 1024L * 1024L * 32L)

int main(int argc, char *argv[]) {
    struct timeval tv1, tv2;
    int *a;
    long i, k, length_mod;
    long arr_len[] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384,
                      32768, 65536, 131072, 262144, 524288, 1048576,
                      2097152, 4194304, 8388608, 16777216};
    a = (int *) calloc(SIZE, sizeof(int));
    if (!a)
        errx(EXIT_FAILURE, "can not allocate array");
    printf("array size,time\n");
    for (k = 0; k < 18; k++) {
        length_mod = arr_len[k] - 1;
        gettimeofday(&tv1, NULL);
        for (i = 0; i < SIZE; i++)
            a[(i*16) & length_mod] += 3;
        gettimeofday(&tv2, NULL);
        printf("%ld,%.6f\n", arr_len[k],
               ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
               ((double) tv2.tv_sec - tv1.tv_sec));
    }
    free(a);
    return EXIT_SUCCESS;
}

