#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_LEN 80

int main(int argc, char *argv[]) {
    char app_id[MAX_LEN] = APP_ID;
    int rank, size, color;
    MPI_Comm local_comm;

    /* usual MPI setup */
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("%s: %d out of %d\n", app_id, rank, size);

    /* barrier for convenience, so that output is easier to interprete */
    MPI_Barrier(MPI_COMM_WORLD);

    /* determine "color", i.e., whether this process is part of applicaton
     * 1 or application 2, and split MPI_COMM_WORLD accordingly */
    if (!strcmp(app_id, "application 1"))
        color = 0;
    else
        color = 1;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &local_comm);

    /* determine size and rank of new communicator */
    MPI_Comm_rank(local_comm, &rank);
    MPI_Comm_size(local_comm, &size);
    printf("%s: %d out of %d\n", app_id, rank, size);

    /* clean up */
    MPI_Comm_free(&local_comm);
    MPI_Finalize();

    return EXIT_SUCCESS;
}
