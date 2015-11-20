#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double *init_array(int n);
void fill_array(double *array, int n);
double avg_matrix(double *array, int n);

int main(int argc, char *argv[]) {
    int rank, size, array_size, nr_iters, iter;
    double *array1, *array2, *result, *tmp;
    MPI_Request request;
    MPI_Status status;
    double start_time, end_time,
           nonblocking_time = 0.0, blocking_time = 0.0;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        if (argc == 3) {
            array_size = atoi(argv[1]);
            nr_iters = atoi(argv[2]);
        } else {
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        result = init_array(array_size);
    }
    MPI_Bcast(&array_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&nr_iters, 1, MPI_INT, 0, MPI_COMM_WORLD);
    array1 = init_array(array_size);
    array2 = init_array(array_size);
    fill_array(array1, array_size);
    MPI_Ireduce(array1, result, array_size, MPI_DOUBLE, MPI_SUM, 0,
                MPI_COMM_WORLD, &request);
    fill_array(array2, array_size);
    MPI_Wait(&request, &status);
    tmp = array1;
    array1 = array2;
    array2 = tmp;
    for (iter = 1; iter < nr_iters; iter++) {
        start_time = MPI_Wtime();
        MPI_Ireduce(array1, result, array_size, MPI_DOUBLE, MPI_SUM, 0,
                    MPI_COMM_WORLD, &request);
        fill_array(array2, array_size);
        MPI_Wait(&request, &status);
        tmp = array1;
        array1 = array2;
        array2 = tmp;
        if (rank == 0) {
            printf("%d: %lf\n", iter, avg_matrix(result, array_size));
        }
        end_time = MPI_Wtime();
        nonblocking_time +=  end_time - start_time;
        start_time = MPI_Wtime();
        MPI_Reduce(array1, result, array_size, MPI_DOUBLE, MPI_SUM, 0,
                   MPI_COMM_WORLD);
        fill_array(array2, array_size);
        tmp = array1;
        array1 = array2;
        array2 = tmp;
        if (rank == 0) {
            printf("%d: %lf\n", iter, avg_matrix(result, array_size));
        }
        end_time = MPI_Wtime();
        blocking_time +=  end_time - start_time;
    }
    if (rank == 0) {
        printf("time for MPI_Reduce: %f for %d iterations\n",
               blocking_time, nr_iters);
        printf("time for MPI_Ireduce: %f for %d iterations\n",
               nonblocking_time, nr_iters);
    }
    free(array1);
    free(array2);
    if (rank == 0) {
        free(result);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

double *init_array(int n) {
    double *array;
    if ((array = (double *) malloc(n*sizeof(double))) == NULL) {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        fprintf(stderr, "process %d: can't allocate array1 (%d bytes)",
                rank, n);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    return array;
}

void fill_array(double *array, int n) {
    int i, flag;
    MPI_Status status;
    for (i = 0; i < n; i++) {
        array[i] = ((double) rand())/((double) RAND_MAX);
    }
}

double avg_matrix(double *array, int n) {
    int i, size;
    double sum = 0.0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum/(n*size);
}
