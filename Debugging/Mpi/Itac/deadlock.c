#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAG 17

int main() {
    const int nr_rounds = 4;
    int rank, size, i, left, right, buffer;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    left = rank == 0 ? size - 1 : rank - 1;
    right = rank == size - 1 ? 0 : rank + 1;
    for (i = 0; i < nr_rounds; i++) {
        MPI_Ssend(&rank, 1, MPI_INT, right, TAG, MPI_COMM_WORLD);
        MPI_Recv(&buffer, 1, MPI_INT, left, TAG, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        printf("rank %d received %d\n", rank, buffer);
    }
    MPI_Finalize();
    return 0;
}
