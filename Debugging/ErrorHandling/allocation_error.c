#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#define MEM_ALLOC_ERR 11

double *create_vector(unsigned long size) {
    double *data;
    if (!(data = (double *) malloc(size*sizeof(double))))
        errx(MEM_ALLOC_ERR,
             "%s:%d (%s): can't allocate data of size %ld\n",
             __FILE__, __LINE__, __func__,  size);
    return data;
}

int main(int argc, char *argv[]) {
    unsigned long size = 10;
    if (argc > 1)
        size = atol(argv[1]);
    double *data = create_vector(size);
    for (unsigned long i = 0; i < size; i++)
        data[i] = (double) i;
    free(data);
    return 0;
}
