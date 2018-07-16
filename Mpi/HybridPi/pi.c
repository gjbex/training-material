#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef WITH_MPI
#include <mpi.h>
#endif
#ifdef _OPENMP
#include <omp.h>
#endif

typedef struct {
    long n;
    int is_verbose;
} Params;

Params get_params(int argc, char *argv[]);
double *compute_limits();
double partial_pi(double left, double right, Params *params);
#ifdef WITH_MPI
MPI_Datatype *alloc_mpi_params_type();
void free_mpi_params_type(MPI_Datatype *params_type);
#endif

int main(int argc, char *argv[]) {
#ifdef WITH_MPI
    const int root = 0;
#endif
    int rank = 0, size = 1;
    Params params;
    double *limits = NULL, local_limits[2], partial_result, result = 0.0;
#ifdef WITH_MPI
#ifdef _OPENMP
    int thread_level;
    MPI_Init_thread(NULL, NULL, MPI_THREAD_FUNNELED, &thread_level);
    if (thread_level != MPI_THREAD_FUNNELED) {
        fprintf(stderr, "thread level funneled not supported\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
#else
    MPI_Init(NULL, NULL);
#endif
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif
    if (rank == 0) {
        params = get_params(argc, argv);
        limits = compute_limits();
    }
#ifdef WITH_MPI
    MPI_Datatype *params_type = alloc_mpi_params_type();
    MPI_Bcast(&params, 1, *params_type, root, MPI_COMM_WORLD);
    free_mpi_params_type(params_type);
    MPI_Scatter(limits, 2, MPI_DOUBLE, local_limits, 2, MPI_DOUBLE, root,
                MPI_COMM_WORLD);
#else
    local_limits[0] = limits[0];
    local_limits[1] = limits[1];
#endif
    if (rank == 0) {
        free(limits);
    }
    if (params.is_verbose)
        printf("rank %d out of %d: %.5lf -> %.5lf (%ld)\n",
               rank, size, local_limits[0], local_limits[1], params.n);
    partial_result = partial_pi(local_limits[0], local_limits[1], &params);
#ifdef WITH_MPI
    MPI_Reduce(&partial_result, &result, 1, MPI_DOUBLE, MPI_SUM, root,
               MPI_COMM_WORLD);
#else
    result = partial_result;
#endif
    if (rank == 0) {
        printf("pi = %.8lf\n", result);
    }
#ifdef WITH_MPI
    MPI_Finalize();
#endif
    return EXIT_SUCCESS;
}

Params get_params(int argc, char *argv[]) {
    int size = 1;
    Params params;
#ifdef WITH_MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif
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
    int i, size = 1;
    double *limits, delta;
#ifdef WITH_MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif
    delta = 1.0/size;
    if ((limits = (double *) malloc(2*size*sizeof(double))) == NULL) {
        warnx("can not allocate array of %d elements", 2*size);
#ifdef WITH_MPI
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
#else
        exit(EXIT_FAILURE);
#endif
    }
    for (i = 0; i < size; i++) {
        limits[2*i] = i*delta;
        limits[2*i + 1] += (i + 1)*delta;
    }
    return limits;
}

double partial_pi(double left, double right, Params *params) {
    int rank = 0;
    double sum = 0.0, result;
    double delta = (right - left)/params->n;
#ifdef WITH_MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif
#pragma omp parallel default(none) \
    shared(sum, delta, left, right, result, params, rank)
    {
        long i;
        double x;
        if (params->is_verbose) {
            int thread_num = 0, num_threads = 1;
#ifdef _OPENMP
            thread_num = omp_get_thread_num();
            num_threads = omp_get_num_threads();
#endif
            printf("thread %d out of %d at rank %d\n",
                   thread_num, num_threads, rank);
        }
#pragma omp for reduction(+:sum)
        for (i = 0; i < params->n; i++) {
            x = left + i*delta;
            sum += 4.0/(1.0 + x*x);
        }
#pragma omp single
        result = sum*delta;
    }
    return result;
}

#ifdef WITH_MPI
MPI_Datatype *alloc_mpi_params_type() {
    const int type_count = 2;
    int block_lengths[] = {1, 1};
    MPI_Aint displacements[] = {0, sizeof(long)};
    MPI_Datatype types[] = {MPI_LONG, MPI_INT};
    MPI_Datatype *params_type;
    if (!(params_type = (MPI_Datatype *) malloc(sizeof(MPI_Datatype)))) {
        warnx("can ot allocate MPI data type");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    MPI_Type_create_struct(type_count, block_lengths, displacements, types,
                           params_type);
    MPI_Type_commit(params_type);
    return params_type;
}

void free_mpi_params_type(MPI_Datatype *params_type) {
    MPI_Type_free(params_type);
    free(params_type);
}
#endif
