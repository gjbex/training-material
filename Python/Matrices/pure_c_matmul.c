#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

double **create_matrix(int n);
void init_matrix(double **m, int n);
void dot_matrix(double **a, double **b, double **c, int n);
void free_matrix(double **m, int n);

int main(int argc, char *argv[]) {
    struct timeval startTime, endTime;
    double **a, **b, **c;
    int n = 5;
    if (argc > 1)
        n = atoi(argv[1]);
    printf("initializing a...\n");
    gettimeofday(&startTime, NULL);
    a = create_matrix(n);
    init_matrix(a, n);
    gettimeofday(&endTime, NULL);
    printf("initialized a: %f\n", endTime.tv_sec - startTime.tv_sec +
            (endTime.tv_usec - startTime.tv_usec)*1e-6);
    printf("initializing b...\n");
    gettimeofday(&startTime, NULL);
    b = create_matrix(n);
    init_matrix(b, n);
    gettimeofday(&endTime, NULL);
    printf("initialized b: %f\n", endTime.tv_sec - startTime.tv_sec +
            (endTime.tv_usec - startTime.tv_usec)*1e-6);
    c = create_matrix(n);
    printf("multiplying...\n");
    gettimeofday(&startTime, NULL);
    dot_matrix(a, b, c, n);
    gettimeofday(&endTime, NULL);
    printf("multiplied: %f\n", endTime.tv_sec - startTime.tv_sec +
            (endTime.tv_usec - startTime.tv_usec)*1e-6);

    free_matrix(a, n);
    free_matrix(b, n);
    free_matrix(c, n);
    return EXIT_SUCCESS;
}

double **create_matrix(int n) {
    double **m;
    int i;
    if (!(m = (double **) malloc(n*sizeof(double *))))
        errx(EXIT_FAILURE, "can not allocate matrix");
    for (i = 0; i < n; i++)
        if (!(m[i] = (double *) malloc(n*sizeof(double))))
            errx(EXIT_FAILURE, "can not allocate matrix row %d", i);
    return m;
}

void init_matrix(double **m, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            m[i][j] = ((double) rand())/((double) RAND_MAX);
}

void dot_matrix(double **a, double **b, double **c, int n) {
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            c[i][j] = 0.0;
            for (k = 0; k < n; k++)
                c[i][j] += a[i][k]*b[k][j];
        }
}

void free_matrix(double **m, int n) {
    int i;
    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

