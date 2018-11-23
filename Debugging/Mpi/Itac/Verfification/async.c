#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
    const int tag = 17;
    const int root = 0;
    int my_rank, my_size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &my_size);
    int sbuff = my_rank, rbuff = -1;
    int partner = (my_rank + 1 + my_size) % my_size;
    MPI_Request request;
    MPI_Irecv(&rbuff, 1, MPI_INT, partner, tag, MPI_COMM_WORLD,
              &request);
    MPI_Send(&sbuff, 1, MPI_INT, partner, tag, MPI_COMM_WORLD);
    printf("rank %d recieved %d from %d\n", my_rank, rbuff, partner);
    // MPI_Wait(&request, MPI_STATUS_IGNORE);
    MPI_Finalize();
    return 0;
}
