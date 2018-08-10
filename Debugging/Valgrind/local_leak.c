#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double *create_weights(int n);
double weighted_sum(double x[], int n);
void produce_data(double data[], int n);

int main() {
    const int nr_iters = 3;
    for (int i = 0; i < nr_iters; i++) {
        int nr_items = i + 3;
        double *data = (double *) malloc(nr_items*sizeof(double));
        produce_data(data, nr_items);
        double sum = weighted_sum(data, nr_items);
        printf("sum = %lf\n", sum);
        free(data);
    }
    return 0;
}

double *create_weights(int n) {
    double *weights = (double *) malloc(n*sizeof(double));
    for (int i = 0; i < n; i++)
        weights[i] = exp(-i);
    return weights;
}

double weighted_sum(double x[], int n) {
    double *weights = create_weights(n);
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += x[i]*weights[i];
    return sum;
}

void produce_data(double data[], int n) {
    for (int i = 0; i < n; i++)
        data[i] = ((double) rand())/RAND_MAX;
}
