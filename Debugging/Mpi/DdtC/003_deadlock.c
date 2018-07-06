#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int root = 0;
    const int tag = 13;
    int rank, size, factor, value, left, right, buffer;
    MPI_Request request;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == root) {
        if (argc < 2) {
            fprintf(stderr, "### error: missing argument\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        factor = atoi(argv[1]);
    } else {
        MPI_Bcast(&factor, 1, MPI_INT, root, MPI_COMM_WORLD);
    }
    value = factor*rank;
    left = (rank - 1 + size) % size;
    right = (rank + 1) % size;
    MPI_Isend(&value, 1, MPI_INT, right, tag, MPI_COMM_WORLD,
              &request);
    MPI_Recv(&buffer, 1, MPI_INT, left, tag, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    printf("rank %d computed %d, received %d\n",
           rank, value, buffer);
    MPI_Finalize();
    return 0;
}
