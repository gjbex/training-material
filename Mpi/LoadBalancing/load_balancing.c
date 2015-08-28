#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

void compute_bounds(int size, int rank, int n, int *lbound, int *rbound);

int main(int argc, char *argv[]) {
    int rank, size, n = 1003, lbound, ubound, i;
    MPI_Init(NULL, NULL);
    if (argc > 1)
        n = atoi(argv[1]);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    compute_bounds(size, rank, n, &lbound, &ubound);
    for (i = 0; i < size; i++) {
        if (rank == i) {
            printf("%3d %10d %10d\n", rank, lbound, ubound);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

void compute_bounds(int size, int rank, int n, int *lbound, int *ubound) {
    int chunk_size = n/size, rest = n % size;
    *lbound = MIN(rank, size - rest)*chunk_size +
              MAX(0, rank - (size - rest))*(chunk_size + 1);
    *ubound = *lbound + (rank >= size - rest ? chunk_size + 1 : chunk_size);
}
