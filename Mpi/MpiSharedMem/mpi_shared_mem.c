#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc __attribute__((unused)),
         char *argv[] __attribute__((unused))) {
    const int disp_unit = sizeof(double);
    MPI_Aint local_win_size = 2;
    double *base_ptr;
    MPI_Win sm_win;
    int global_rank, global_size, sm_rank, sm_size, i;
    MPI_Comm sm_comm;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &global_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
    /* split the communicator in shared memory subcommuniccators
       and determine rank and size */
    MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, 0,
                        MPI_INFO_NULL, &sm_comm);
    MPI_Comm_size(sm_comm, &sm_size);
    MPI_Comm_rank(sm_comm, &sm_rank);
    if (global_rank == 0) {
        printf("SM size: %d, global size: %d\n", sm_size, global_size);
    }
    MPI_Win_allocate_shared(local_win_size*disp_unit, disp_unit,
                            MPI_INFO_NULL, sm_comm, &base_ptr, &sm_win);
    /* local load/sotre epoch */
    MPI_Win_fence(0, sm_win);
    for (i = 0; i < local_win_size; i++)
        base_ptr[i] = (i + 1)*1.0e3 + global_rank*1.0e4;
    MPI_Win_fence(0, sm_win);
    /* accessing neighbour's memory for load */
    if (sm_rank > 0)
        printf("%d's left neighbour has %.1lf as last value\n",
               global_rank, base_ptr[-1]);
    if (sm_rank < sm_size - 1)
        printf("%d's right neighbour has %.1lf as first value\n",
               global_rank, base_ptr[local_win_size]);
    MPI_Win_free(&sm_win);
    MPI_Finalize();
    return EXIT_SUCCESS;
}
