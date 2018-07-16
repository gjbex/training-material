#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NR_DIMS 2

int main(int argc, char *argv[]) {
    const int periodic[NR_DIMS] = {0, 0};
    const int reorder = 0;
    const int local_rows = 3, local_cols = 4;
    int proc_rows, proc_cols;
    int row, col, proc_row, proc_col;
    int rank, size;
    int dims[NR_DIMS] = {0, 0};
    int cart_coords[NR_DIMS];
    int *data;
    int data_size = local_rows*local_cols*sizeof(int);
    MPI_Comm cart_comm;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Dims_create(size, NR_DIMS, dims);
    proc_rows = dims[0];
    proc_cols = dims[1];
    MPI_Cart_create(MPI_COMM_WORLD, NR_DIMS, dims, periodic, reorder,
                    &cart_comm);
    if (!(data = (int *) malloc(data_size))) {
        fprintf(stderr, "### error: rank %d can't allocate memory\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Cart_coords(cart_comm, rank, NR_DIMS, cart_coords);
    proc_row = cart_coords[0];
    proc_col = cart_coords[1];
    fprintf(stderr, "rank %d: (%d, %d)\n", rank,
            cart_coords[0], cart_coords[1]);
    for (row = 0; row < local_rows; row++)
        for (col = 0; col < local_cols; col++) {
            int value = proc_row*local_rows*local_cols*proc_cols +
                row*local_cols*proc_cols + col + proc_col*local_cols;
            data[row*local_cols + col] = value;
        }
    MPI_Barrier(MPI_COMM_WORLD);
    free(data);
    MPI_Finalize();
    return 0;
}
