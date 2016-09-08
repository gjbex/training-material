#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_LEN 80

int main(int argc, char *argv[]) {
    int rank, size;
    char name[MAX_LEN];
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    strncpy(name, argv[0], MAX_LEN);
    printf("%s: %d out of %d\n", name, rank, size);
    MPI_Finalize();
    return EXIT_SUCCESS;
}
