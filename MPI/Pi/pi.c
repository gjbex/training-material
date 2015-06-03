#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double compute_pi(long n);

int main(int argc, char *argv[]) {
    int rank, size;
    long n;
    double pi, global_pi;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(rank);
    if (rank == 0) {
        if (argc < 2) {
            n = 1000;
        } else {
            n = atol(argv[1]);
        }
        n /= size;
    }
    MPI_Bcast(&n, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    pi = compute_pi(n);
    printf("rank %d: %ld, %.5f\n", rank, n, pi);
    MPI_Reduce(&pi, &global_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("pi = %.5f\n", global_pi/size);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

double compute_pi(long n) {
    long i;
    double count = 0.0, x, y;
#pragma omp parallel for private(x, y) reduction(+:count)
    for (i = 0; i < n; i++) {
        x = ((double) rand())/RAND_MAX;
        y = ((double) rand())/RAND_MAX;
        if (x*x + y*y <= 1.0) {
            count += 1.0;
        }
    }
    return 4.0*count/n;
}
