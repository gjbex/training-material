#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAG 17

int main() {
    const int nr_rounds = 4;
    int rank, size, i, left, right, in_buffer, out_buffer;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    left = rank == 0 ? size - 1 : rank - 1;
    right = rank == size - 1 ? 0 : rank + 1;
    out_buffer = rank;
    for (i = 0; i < nr_rounds; i++) {
        if (rank % 2 == 0) {
            MPI_Ssend(&out_buffer, 1, MPI_INT, right, TAG, MPI_COMM_WORLD);
            MPI_Recv(&in_buffer, 1, MPI_INT, left, TAG, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
        } else {
            MPI_Recv(&in_buffer, 1, MPI_INT, left, TAG, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            MPI_Ssend(&out_buffer, 1, MPI_INT, right, TAG, MPI_COMM_WORLD);
        }
        printf("rank %d received %d\n", rank, in_buffer);
        out_buffer = in_buffer;
    }
    MPI_Finalize();
    return 0;
}
