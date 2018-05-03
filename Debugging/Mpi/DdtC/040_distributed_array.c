#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

#define NR_DIMS 2

int main(int argc, char *argv[]) {
    const int periodic[NR_DIMS] = {0, 0};
    const int reorder = 0;
    const int local_rows = 300, local_cols = 400;
    int proc_rows, proc_cols;
    int row, col;
    int rank, size;
    int dims[NR_DIMS] = {0, 0};
    int cart_coords[NR_DIMS];
    double sum = 0.0, avg;
    double *data;
    int data_size = local_rows*local_cols*sizeof(double);
    MPI_Comm cart_comm;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Dims_create(size, NR_DIMS, dims);
    MPI_Cart_create(MPI_COMM_WORLD, NR_DIMS, dims, periodic, reorder,
                    &cart_comm);
    if (!(data = (double *) malloc(data_size))) {
        fprintf(stderr, "### error: rank %d can't allocate memory\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Cart_coords(cart_comm, rank, NR_DIMS, cart_coords);
    fprintf(stderr, "rank %d: (%d, %d)\n", rank,
            cart_coords[0], cart_coords[1]);
    srand(rank);
    for (row = 0; row < local_rows; row++)
        for (col = 0; col < local_cols; col++)
            data[row*local_cols + col] = ((double) rand())/RAND_MAX;
#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        printf("rank %d:%d has %d threads\n", rank, thread_num, omp_get_num_threads());
#pragma omp for reduction(+:sum)
        for (row = 0; row < local_rows; row++) {
            int col;
            for (col = 0; col < local_cols; col++)
                sum += data[row*local_cols + col];
        }
    }
    MPI_Reduce(&sum, &avg, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("average = %le\n", avg);
    free(data);
    MPI_Finalize();
    return 0;
}
