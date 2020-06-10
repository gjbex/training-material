#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
    const int tag = 17;
    MPI_Init(NULL, NULL);
    int my_rank, my_size;
    MPI_Comm_size(MPI_COMM_WORLD, &my_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int neighbours[2] = {(my_rank + my_size - 1) % my_size, (my_rank + 1) % my_size};
    double send_buff[2] = {1.1*(1 + my_rank), 1.2*(1 + my_rank)};
    double recv_buffer[2];
    MPI_Request requests[2];
    MPI_Status statusses[2];
    for (int iter = 0; iter < 5; ++iter) {
        for (int i = 0; i < 2; ++i) {
            MPI_Isend(&(send_buff[i]), 1, MPI_DOUBLE, neighbours[i], tag,
                    MPI_COMM_WORLD, &(requests[i]));
        }
        for (int i = 0; i < 2; ++i) {
            MPI_Recv(&(recv_buffer[i]), 1, MPI_DOUBLE, neighbours[i], tag,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d received %.1lf from %d\n", my_rank, recv_buffer[i],
                    neighbours[i]);
        }
        MPI_Waitall(2, requests, statusses);
        for (int i = 0; i < 2; ++i) {
            send_buff[i] = recv_buffer[i];
        }
        MPI_Barrier(MPI_COMM_WORLD);
        if (my_rank == 0) {
            printf("---------------------------------------\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
