#ifndef VECTORS_HDR
#define VECTORS_HDR

typedef struct {
    double *element;
    int n;
} Vector;

Vector *init_vector(int n);
Vector *sum_vectors(Vector *vectors[], int n);
void fill_vector(Vector *v, double start_value, double delta_value);
double vector_length(Vector *v);
void print_vector(Vector *v);
void free_vector(Vector *v);

#endif
