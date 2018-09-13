#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "vectors.h"

int main() {
    int vector_len = 5;
    int nr_vectors = 3;
    Vector **vectors = (Vector **) malloc(nr_vectors*sizeof(Vector *));
    if (vectors == NULL)
        errx(EXIT_FAILURE, "can't allocate %d vectors", nr_vectors);
    
    for (int j = 0; j < nr_vectors; j++) {
        vectors[j] = init_vector(vector_len);
        fill_vector(vectors[j], j, 0.1*(j + 1.0));
        print_vector(vectors[j]);
    }
    Vector *sum = sum_vectors(vectors, nr_vectors);
    print_vector(sum);
    double length = vector_length(sum);
    printf("length = %.5le\n", length);
    free_vector(sum);
    for (int j = 0; j < nr_vectors; j++)
        free_vector(vectors[j]);
    free(vectors);
    nr_vectors = 100;
    Vector *vectors2[nr_vectors];
    for (int j = 0; j < nr_vectors; j++) {
        vectors2[j] = init_vector(vector_len);
        fill_vector(vectors2[j], j, 0.1*(j + 1.0));
        // print_vector(vectors2[j]);
    }
    double avg_length = 0.0;
    for (int j = 0; j < nr_vectors; j++)
        avg_length += vector_length(vectors2[j]);
    printf("average length = %.5le\n", avg_length/nr_vectors);
    for (int j = 0; j < nr_vectors; j++)
        free_vector(vectors2[j]);
    return 0;
}
