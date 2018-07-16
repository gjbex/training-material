#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *arcv) {
    const int root = 0;
    int rank, size;
    double *root_buffer;
    double val_buffer;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == root) {
        int i;
        root_buffer = (double *) malloc(size*sizeof(double));
        if (root_buffer == 0)
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        for (i = 0; i < size; i++)
            root_buffer[i] = (double) i;
    }
    MPI_Scatter(root_buffer, 1, MPI_DOUBLE,
                &val_buffer, 1, MPI_DOUBLE,
                root, MPI_COMM_WORLD);
    printf("rank %d received %.2lf\n", rank, val_buffer);
    val_buffer *= val_buffer;
    MPI_Gather(&val_buffer, 1, MPI_DOUBLE,
               root_buffer, 1, MPI_DOUBLE,
               root, MPI_COMM_WORLD);
    if (rank == root) {
        int i;
        printf("root received: ");
        for (i = 0; i < size; i++)
            printf("%.1lf ", root_buffer[i]);
        printf("\n");
        free(root_buffer);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
