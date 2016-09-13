#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_LEN 80
#define TAG 11

int main(int argc, char *argv[]) {
    char app_id[MAX_LEN] = APP_ID;
    char buff[MAX_LEN];
    int rank, size, color, local_rank, local_size, appl1_root, appl2_root,
        int_buff;
    MPI_Comm local_comm;
    MPI_Status status;

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
        color = 1;
    else
        color = 2;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &local_comm);

    /* determine size and rank of new communicator */
    MPI_Comm_rank(local_comm, &local_rank);
    MPI_Comm_size(local_comm, &local_size);

    /* figure out which global rank is going to be root for application 1
     * and application 2, send the result to global rank 0 */
    if (color == 1)
        int_buff = rank;
    else
        int_buff = size;
    MPI_Allreduce(&int_buff, &appl1_root, 1, MPI_INT, MPI_MIN,
                  MPI_COMM_WORLD);
    if (color == 2)
        int_buff = rank;
    else
        int_buff = size;
    MPI_Allreduce(&int_buff, &appl2_root, 1, MPI_INT, MPI_MIN,
                  MPI_COMM_WORLD);

    printf("%s: %d out of %d, root = %d\n",
           app_id, local_rank, local_size,
           color == 1 ? appl1_root : appl2_root);

    /* barrier for convenience, so that output is easier to interprete */
    MPI_Barrier(MPI_COMM_WORLD);

    /* send greetings from application 1 to application 2 */
    if (rank == appl1_root) {
        sprintf(buff, "%s greetings!", app_id);
        MPI_Ssend(buff, MAX_LEN, MPI_CHAR, appl2_root, TAG, MPI_COMM_WORLD);
    } else if (rank == appl2_root) {
        MPI_Recv(buff, MAX_LEN, MPI_CHAR, appl1_root, TAG, MPI_COMM_WORLD,
                 &status);
    }
    if (color == 2) {
        MPI_Bcast(buff, MAX_LEN, MPI_CHAR, 0, local_comm);
        printf("%s rank %d received '%s'\n", app_id, local_rank, buff);
    }

    /* send greetings from application 2 to application 1 */
    if (rank == appl2_root) {
        sprintf(buff, "%s greetings!", app_id);
        MPI_Ssend(buff, MAX_LEN, MPI_CHAR, appl1_root, TAG, MPI_COMM_WORLD);
    } else if (rank == appl1_root) {
        MPI_Recv(buff, MAX_LEN, MPI_CHAR, appl2_root, TAG, MPI_COMM_WORLD,
                 &status);
    }
    if (color == 1) {
        MPI_Bcast(buff, MAX_LEN, MPI_CHAR, 0, local_comm);
        printf("%s rank %d received '%s'\n", app_id, local_rank, buff);
    }

    /* clean up */
    MPI_Comm_free(&local_comm);
    MPI_Finalize();

    return EXIT_SUCCESS;
}
