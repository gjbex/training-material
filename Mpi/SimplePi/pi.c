#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

typedef struct {
    long n;
    int is_verbose;
} Params;

Params get_params(int argc, char *argv[]);
double *compute_limits();
double partial_pi(double left, double right, long n);

int main(int argc, char *argv[]) {
    const int root = 0;
    int rank;
    Params params;
    const int type_count = 2;
    int block_lengths[] = {1, 1};
    MPI_Aint displacements[] = {0, sizeof(long)};
    MPI_Datatype types[] = {MPI_LONG, MPI_INT};
    MPI_Datatype params_type;
    double *limits, local_limits[2], partial_result, result = 0.0;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Type_create_struct(type_count, block_lengths, displacements, types,
                           &params_type);
    MPI_Type_commit(&params_type);
    if (rank == 0) {
        params = get_params(argc, argv);
    }
    MPI_Bcast(&params, 1, params_type, root, MPI_COMM_WORLD);
    if (rank == 0) {
        limits = compute_limits();
    }
    MPI_Scatter(limits, 2, MPI_DOUBLE, local_limits, 2, MPI_DOUBLE, root,
               MPI_COMM_WORLD);
    if (rank == 0) {
        free(limits);
    }
    if (params.is_verbose)
        printf("rank %d: %.5lf -> %.5lf (%ld)\n",
               rank, local_limits[0], local_limits[1], params.n);
    partial_result = partial_pi(local_limits[0], local_limits[1], params.n);
    MPI_Reduce(&partial_result, &result, 1, MPI_DOUBLE, MPI_SUM, root,
               MPI_COMM_WORLD);
    if (rank == 0) {
        printf("pi = %.8lf\n", result);
    }
    MPI_Type_free(&params_type);
    MPI_Finalize();
    return EXIT_SUCCESS;
}

Params get_params(int argc, char *argv[]) {
    int size;
    Params params;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (argc > 1)
        params.n = atol(argv[1]);
    else
        params.n = 1000;
    params.n = params.n/size;
    if (argc > 2)
        params.is_verbose = atoi(argv[2]);
    else
        params.is_verbose = 0;
    return params;
}

double *compute_limits() {
    int i, size;
    double *limits, delta;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    delta = 1.0/size;
    if ((limits = (double *) malloc(2*size*sizeof(double))) == NULL) {
        warnx("can not allocate array of %d elements", 2*size);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    for (i = 0; i < size; i++) {
        limits[2*i] = i*delta;
        limits[2*i + 1] += (i + 1)*delta;
    }
    return limits;
}

double partial_pi(double left, double right, long n) {
    double sum = 0;
    double delta = (right - left)/n;
    double x;
    for (x = left; x < right; x += delta)
        sum += 4.0/(1.0 + x*x);
    return sum*delta;
}
