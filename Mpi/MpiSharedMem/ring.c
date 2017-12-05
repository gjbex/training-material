#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    const int key = 0, tag = 1;
    const MPI_Aint local_win_size = 1;
    const int disp_unit = sizeof(int);
    int global_rank, global_size, sm_rank, sm_size, nr_nodes, i,
        source, dest;
    MPI_Comm sm_comm, node_comm;
    MPI_Win sm_win;
    MPI_Request request;
    int send_buffer, recv_buffer, *base_ptr, total = 0;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &global_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
    /* set up the shared memory communicators */
    MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, key,
                        MPI_INFO_NULL, &sm_comm);
    MPI_Comm_size(sm_comm, &sm_size);
    MPI_Comm_rank(sm_comm, &sm_rank);
    /* create shared memory window */
    MPI_Win_allocate_shared(local_win_size*disp_unit, disp_unit,
                            MPI_INFO_NULL, sm_comm, &base_ptr, &sm_win);
    MPI_Comm_split(MPI_COMM_WORLD, sm_rank == 0, key, &node_comm);
    MPI_Comm_size(node_comm, &nr_nodes);
    /* local store epoch */
    MPI_Win_fence(0, sm_win);
    base_ptr[0] = global_rank;
    MPI_Win_fence(0, sm_win);
    /* initialize send buffer */
    if (sm_rank == sm_size - 1) {
        int i;
        send_buffer = 0;
        for (i = 0; i < sm_size; i++)
            send_buffer += base_ptr[-i];
    }
    /* send data around */
    source = (global_rank - 1 + global_size) % global_size;
    dest = (global_rank + 1) % global_size;
    for (i = 0; i < nr_nodes; i++) {
        int k;
        if (sm_rank == sm_size - 1) {
            printf("%2d sending to %2d\n", global_rank, dest);
            MPI_Issend(&send_buffer, 1, MPI_INT, dest, tag,
                       MPI_COMM_WORLD, &request);
        }
        if (sm_rank == 0) {
            printf("%d receiving from %d\n", global_rank, source);
            MPI_Recv(&recv_buffer, 1, MPI_INT, source, tag,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        /* start local epoch */
        MPI_Win_fence(0, sm_win);
        if (sm_rank == 0) {
            int i;
            for (i = 0; i < sm_size; i++)
                base_ptr[i] = recv_buffer;
        }
        total += base_ptr[0];
        MPI_Win_fence(0, sm_win);
        if (sm_rank == sm_size - 1) {
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            send_buffer = base_ptr[0];
        }
        printf("round %2d done for rank %2d\n", i, global_rank);
    }
    printf("rank %2d: %2d\n", global_rank, total);
    MPI_Win_free(&sm_win);
    MPI_Finalize();
    return EXIT_SUCCESS;
}
