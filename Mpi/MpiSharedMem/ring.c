#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    const int key = 0, tag = 1;
    const MPI_Aint local_win_size = 1;
    const int disp_unit = sizeof(int);
    int global_rank, global_size, sm_rank, sm_size, nr_nodes, i,
        source, dest;
    int verbose = 0;
    MPI_Comm sm_comm, node_comm;
    MPI_Win sm_win;
    MPI_Request request;
    int send_buffer, recv_buffer, *base_ptr, total = 0;

    /* set up MPI */
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &global_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);

    /* deal with command line arguments */
    if (global_rank == 0 && argc > 1)
        verbose = atoi(argv[1]);
    MPI_Bcast(&verbose, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* set up the shared memory communicators */
    MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, key,
                        MPI_INFO_NULL, &sm_comm);
    MPI_Comm_size(sm_comm, &sm_size);
    MPI_Comm_rank(sm_comm, &sm_rank);

    /* create shared memory window */
    MPI_Win_allocate_shared(local_win_size*disp_unit, disp_unit,
                            MPI_INFO_NULL, sm_comm, &base_ptr, &sm_win);
    MPI_Comm_split(MPI_COMM_WORLD, sm_rank == 0, key, &node_comm);
    if (global_rank == 0) {
        MPI_Comm_size(node_comm, &nr_nodes);
        if (verbose)
            fprintf(stderr, "running on %d shared memory nodes\n",
                    nr_nodes);
    }
    MPI_Bcast(&nr_nodes, 1, MPI_INT, 0, MPI_COMM_WORLD);

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
        if (sm_rank == sm_size - 1) {
            if (verbose)
                fprintf(stderr, "%2d sending to %2d\n", global_rank, dest);
            MPI_Issend(&send_buffer, 1, MPI_INT, dest, tag,
                       MPI_COMM_WORLD, &request);
        }
        if (sm_rank == 0) {
            if (verbose)
                fprintf(stderr, "%d receiving from %d\n",
                        global_rank, source);
            MPI_Recv(&recv_buffer, 1, MPI_INT, source, tag,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        /* start local epoch */
        MPI_Win_fence(0, sm_win);
        if (sm_rank == 0) {
            int k;
            for (k = 0; k < sm_size; k++)
                base_ptr[k] = recv_buffer;
        }
        MPI_Win_fence(0, sm_win);
        total += base_ptr[0];
        if (sm_rank == sm_size - 1) {
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            send_buffer = base_ptr[0];
        }
        if (verbose)
            fprintf(stderr, "round %2d done for rank %2d\n",
                    i, global_rank);
    }
    printf("rank %2d: %2d\n", global_rank, total);
    MPI_Win_free(&sm_win);
    MPI_Finalize();
    return EXIT_SUCCESS;
}
