#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE (64L * 1024L * 1024L * 32L)
#define PAR 32

int main(int argc, char *argv[]) {
    struct timeval tv1, tv2;
    double a[PAR];
    int par, j;
    long i;

    printf("instructions,time dependent,check dependent,"
           "time independent,check independent\n");

    printf("%d", 2);
    for (j = 0; j < PAR; j++)
        a[j] = 0.0;
    gettimeofday(&tv1, NULL);
    for (i = 0; i < SIZE; i++) {
        a[0] += 1.2;
        a[0] += 0.8;
    }
    gettimeofday(&tv2, NULL);
    for (j = 1; j < PAR; j++)
        a[0] += a[j];
    printf(",%.6f,%.2f",
           ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
           ((double) tv2.tv_sec - tv1.tv_sec), a[0]);

    for (j = 0; j < PAR; j++)
        a[j] = 0.0;
    gettimeofday(&tv1, NULL);
    for (i = 0; i < SIZE; i++) {
        a[0] += 1.2;
        a[1] += 0.8;
    }
    gettimeofday(&tv2, NULL);
    for (j = 1; j < PAR; j++)
        a[0] += a[j];
    printf(",%.6f,%.2f\n",
           ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
           ((double) tv2.tv_sec - tv1.tv_sec), a[0]);

    printf("%d", 4);
    for (j = 0; j < PAR; j++)
        a[j] = 0.0;
    gettimeofday(&tv1, NULL);
    for (i = 0; i < SIZE; i++) {
        a[0] += 1.2;
        a[0] += 0.8;
        a[0] += 1.4;
        a[0] += 0.6;
    }
    gettimeofday(&tv2, NULL);
    for (j = 1; j < PAR; j++)
        a[0] += a[j];
    printf(",%.6f,%.2f",
           ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
           ((double) tv2.tv_sec - tv1.tv_sec), a[0]);

    for (j = 0; j < PAR; j++)
        a[j] = 0.0;
    gettimeofday(&tv1, NULL);
    for (i = 0; i < SIZE; i++) {
        a[0] += 1.2;
        a[1] += 0.8;
        a[2] += 1.4;
        a[3] += 0.6;
    }
    gettimeofday(&tv2, NULL);
    for (j = 1; j < PAR; j++)
        a[0] += a[j];
    printf(",%.6f,%.2f\n",
           ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
           ((double) tv2.tv_sec - tv1.tv_sec), a[0]);

    printf("%d", 8);
    for (j = 0; j < PAR; j++)
        a[j] = 0.0;
    gettimeofday(&tv1, NULL);
    for (i = 0; i < SIZE; i++) {
        a[0] += 1.2;
        a[0] += 0.8;
        a[0] += 1.4;
        a[0] += 0.6;
        a[0] += 1.6;
        a[0] += 0.4;
        a[0] += 1.8;
        a[0] += 0.2;
    }
    gettimeofday(&tv2, NULL);
    for (j = 1; j < PAR; j++)
        a[0] += a[j];
    printf(",%.6f,%.2f",
           ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
           ((double) tv2.tv_sec - tv1.tv_sec), a[0]);

    for (j = 0; j < PAR; j++)
        a[j] = 0.0;
    gettimeofday(&tv1, NULL);
    for (i = 0; i < SIZE; i++) {
        a[0] += 1.2;
        a[1] += 0.8;
        a[2] += 1.4;
        a[3] += 0.6;
        a[4] += 1.6;
        a[5] += 0.4;
        a[6] += 1.8;
        a[7] += 0.2;
    }
    gettimeofday(&tv2, NULL);
    for (j = 1; j < PAR; j++)
        a[0] += a[j];
    printf(",%.6f,%.2f\n",
           ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
           ((double) tv2.tv_sec - tv1.tv_sec), a[0]);

    printf("%d", 16);
    for (j = 0; j < PAR; j++)
        a[j] = 0.0;
    gettimeofday(&tv1, NULL);
    for (i = 0; i < SIZE; i++) {
        a[0] += 1.2;
        a[0] += 0.8;
        a[0] += 1.4;
        a[0] += 0.6;
        a[0] += 1.6;
        a[0] += 0.4;
        a[0] += 1.8;
        a[0] += 0.2;
        a[0] += 1.25;
        a[0] += 0.75;
        a[0] += 1.35;
        a[0] += 0.65;
        a[0] += 1.55;
        a[0] += 0.45;
        a[0] += 1.75;
        a[0] += 0.25;
    }
    gettimeofday(&tv2, NULL);
    for (j = 1; j < PAR; j++)
        a[0] += a[j];
    printf(",%.6f,%.2f",
           ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
           ((double) tv2.tv_sec - tv1.tv_sec), a[0]);

    for (j = 0; j < PAR; j++)
        a[j] = 0.0;
    gettimeofday(&tv1, NULL);
    for (i = 0; i < SIZE; i++) {
        a[0] += 1.2;
        a[1] += 0.8;
        a[2] += 1.4;
        a[3] += 0.6;
        a[4] += 1.6;
        a[5] += 0.4;
        a[6] += 1.8;
        a[7] += 0.2;
        a[8] += 1.25;
        a[9] += 0.75;
        a[10] += 1.35;
        a[11] += 0.65;
        a[12] += 1.55;
        a[13] += 0.45;
        a[14] += 1.75;
        a[15] += 0.25;
    }
    gettimeofday(&tv2, NULL);
    for (j = 1; j < PAR; j++)
        a[0] += a[j];
    printf(",%.6f,%.2f\n",
           ((double) tv2.tv_usec - tv1.tv_usec)/1.0e6 +
           ((double) tv2.tv_sec - tv1.tv_sec), a[0]);

    return EXIT_SUCCESS;
}

