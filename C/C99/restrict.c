#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void init_temperature(double T[], int n);
void print_temperature(double T[], int n);
void update_temperature(double * old_T, double * new_T, int n);
void update_temperature_r(double * restrict old_T, double * restrict new_T,
                          int n);
void init_tmp_temperature(double T_tmp[], double T[], int n);

int main(int argc, char *argv[]) {
    struct timeval start_tv, end_tv;
    int n = 10;
    int nr_steps = 100;
    if (argc > 1)
        n = atoi(argv[1]);
    if (argc > 2)
        nr_steps = atoi(argv[2]);
    double T[n*n], T_tmp[n*n];
    srand(1234);
    init_temperature(T, n);
    init_tmp_temperature(T_tmp, T, n);
    print_temperature(T, n);
    printf("\n");
    gettimeofday(&start_tv, NULL);
    for (int step = 0; step < nr_steps/2; step++) {
        update_temperature(T, T_tmp, n);
        update_temperature(T_tmp, T, n);
    }
    gettimeofday(&end_tv, NULL);
    print_temperature(T, n);
    printf("non restrict: %.6lf\n",
            1.0e6*(end_tv.tv_sec - start_tv.tv_sec) +
            (end_tv.tv_usec - start_tv.tv_usec));
    srand(1234);
    init_temperature(T, n);
    init_tmp_temperature(T_tmp, T, n);
    print_temperature(T, n);
    printf("\n");
    gettimeofday(&start_tv, NULL);
    for (int step = 0; step < nr_steps/2; step++) {
        update_temperature_r(T, T_tmp, n);
        update_temperature_r(T_tmp, T, n);
    }
    gettimeofday(&end_tv, NULL);
    print_temperature(T, n);
    printf("restrict: %.6lf\n",
            1.0e6*(end_tv.tv_sec - start_tv.tv_sec) +
            (end_tv.tv_usec - start_tv.tv_usec));
    return EXIT_SUCCESS;
}

void init_temperature(double T[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            T[i*n + j] = ((double) rand())/RAND_MAX;
}

void init_tmp_temperature(double T_tmp[], double T[], int n) {
    for (int i = 0; i < n; i++) {
        T_tmp[i*n] = T[i*n];
        T_tmp[i*n + n - 1] = T[i*n + n - 1];
    }
    for (int j = 0; j < n; j++) {
        T_tmp[j] = T[j];
        T_tmp[(n - 1)*n + j] = T[(n - 1)*n + j];
    }
}

void print_temperature(double T[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%10lf", T[i*n + j]);
        printf("\n");
    }
}

void update_temperature_r(double * restrict old_T, double * restrict new_T,
                          int n) {
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < n - 1; j++)
            new_T[i*n + j] = 0.25*(old_T[i*n + j + 1] +
                                   old_T[i*n + j - 1] +
                                   old_T[(i + 1)*n + j] +
                                   old_T[(i - 1)*n + j]);
}

void update_temperature(double * old_T, double * new_T, int n) {
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < n - 1; j++)
            new_T[i*n + j] = 0.25*(old_T[i*n + j + 1] +
                                   old_T[i*n + j - 1] +
                                   old_T[(i + 1)*n + j] +
                                   old_T[(i - 1)*n + j]);
}
