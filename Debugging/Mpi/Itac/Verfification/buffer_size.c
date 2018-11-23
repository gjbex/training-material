#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
    const int root = 0;
    int buff_size = 5;
    int my_rank, my_size;
    double *sbuff, *rbuff;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &my_size);
    if (my_rank == root + 1)
        buff_size += 3;
    sbuff = (double *) malloc(buff_size*sizeof(double));
    if (my_rank == root)
        rbuff = (double *) malloc(buff_size*sizeof(double));
    for (int i = 0; i < buff_size; i++)
        sbuff[i] = pow(10.0, my_rank)*(1.0 + i);
    MPI_Reduce(sbuff, rbuff, buff_size, MPI_DOUBLE, MPI_SUM, root,
               MPI_COMM_WORLD);
    if (my_rank == root)
        for (int i = 0; i < buff_size; i++)
            printf("%d: %.2f\n", i, rbuff[i]);
    MPI_Finalize();
    return 0;
}
