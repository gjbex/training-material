#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NR_DIMS 2

int main(int argc, char *argv[]) {
    const int periodic[NR_DIMS] = {0, 0};
    const int reorder = 0;
    const int local_x_max = 3, local_y_max = 4;
    int x, y;
    int rank, size;
    int dims[NR_DIMS] = {0, 0};
    int cart_coords[NR_DIMS];
    int *data;
    int data_size = local_x_max*local_y_max*sizeof(int);
    MPI_Comm cart_comm;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Dims_create(size, NR_DIMS, dims);
    MPI_Cart_create(MPI_COMM_WORLD, NR_DIMS, dims, periodic, reorder,
                    &cart_comm);
    if (!(data = (int *) malloc(data_size))) {
        fprintf(stderr, "### error: rank %d can't allocate memory\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Cart_coords(cart_comm, rank, NR_DIMS, cart_coords);
    fprintf(stderr, "rank %d: (%d, %d)\n", rank,
            cart_coords[0], cart_coords[1]);
    for (x = 0; x <= local_x_max; x++)
        for (y = 0; y <= local_y_max; y++) {
            int value = cart_coords[0]*local_x_max +
                y*(1 + cart_coords[1])*local_x_max;
            data[x + y*local_x_max] = value;
        }
    free(data);
    MPI_Finalize();
    return 0;
}
