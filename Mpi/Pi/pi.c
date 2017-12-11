#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>
#ifdef _OPENMP
#include <omp.h>
#endif

double compute_pi(long n, int seed);

int main(int argc, char *argv[]) {
    int rank, size;
    long n;
    double pi, global_pi;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        if (argc < 2) {
            n = 1000;
        } else {
            n = atol(argv[1]);
        }
        n /= size;
    }
    MPI_Bcast(&n, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    pi = compute_pi(n, rank);
    printf("rank %d: %ld, %.5f\n", rank, n, pi);
    MPI_Reduce(&pi, &global_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("pi = %.5f\n", global_pi/size);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

double compute_pi(long n, int rank) {
    double count = 0.0;
#pragma omp parallel shared(count, n, rank) default(none)
    {
        long i;
        struct timeval time;
        gettimeofday(&time, NULL);
        unsigned int seed = (unsigned int) (time.tv_usec*(17*rank + 1) +
                              time.tv_sec/(rank + 1));
#ifdef _OPENMP
        int thread_nr = 0;
        thread_nr = omp_get_thread_num();
        seed += 17*thread_nr;
#endif
#pragma omp for reduction(+:count)
        for (i = 0; i < n; i++) {
            double x = ((double) rand_r(&seed))/RAND_MAX;
            double y = ((double) rand_r(&seed))/RAND_MAX;
            if (x*x + y*y <= 1.0) {
                count += 1.0;
            }
        }
    }
    return 4.0*count/n;
}
