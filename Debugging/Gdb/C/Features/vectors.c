#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "vectors.h"

Vector *init_vector(int n) {
    Vector *v = (Vector *) malloc(sizeof(Vector));
    if (v == NULL)
        errx(EXIT_FAILURE, "can't allocated vector");
    v->element = (double *) malloc(n*sizeof(double));
    if (v->element == NULL)
        errx(EXIT_FAILURE, "can't allocated vector of size %d", n);
    v->n = n;
    for (int i = 0; i < v->n; i++)
        v->element[i] = 0.0;
    return v;
}

void fill_vector(Vector *v, double start_value, double delta_value) {
    for (int i = 0; i < v->n; i++)
        v->element[i] = start_value + i*delta_value;
}

void print_vector(Vector *v) {
    for (int i = 0; i < v->n; i++)
        printf("%.5le%s", v->element[i], i < v->n - 1 ? ", " : "\n");
}

Vector *sum_vectors(Vector *vectors[], int n) {
    Vector *v = init_vector(vectors[0]->n);
    for (int j = 0; j < n; j++)
        for (int i = 0; i < v->n; i++)
            v->element[i] += vectors[j]->element[i];
    return v;
}

double vector_length(Vector *v) {
    double sum = 0.0;
    for (int i = 0; i < v->n; i++)
        sum += v->element[i]*v->element[i];
    return sqrt(sum);
}

void free_vector(Vector *v) {
    free(v->element);
}
