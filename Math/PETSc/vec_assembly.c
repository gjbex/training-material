#include <petscvec.h>

static char help[] = "demonstrates assembling a vector.\n";

int main(int argc, char *argv[]) {
    Vec x;
    PetscInt n = 20, local_size;
    PetscBool show_vector = 0;
    PetscScalar *local_values;
    int rank, i;

    /* initialize PETSc and get options */
    PetscInitialize(&argc, &argv, (char *) 0, help);
    PetscPrintf(PETSC_COMM_WORLD, "PETSc initialized\n");
    PetscOptionsGetInt(NULL, "-n", &n, NULL);
    PetscOptionsGetBool(NULL, "-show_vec", &show_vector, NULL);
    PetscPrintf(PETSC_COMM_WORLD, "vector length = %d\n", (int) n);

    VecCreate(PETSC_COMM_WORLD, &x);
    VecSetSizes(x, PETSC_DECIDE, n);
    VecSetFromOptions(x);

    /* determine local sizes */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    VecGetLocalSize(x, &local_size);
    printf("rank %d: %d\n", rank, (int) local_size);

    /* set the local values to the rank of the MPI process */
    VecGetArray(x, &local_values);
    for (i = 0; i < local_size; i++)
        local_values[i] = (PetscScalar) rank;
    VecAssemblyBegin(x);
    VecAssemblyEnd(x);
    PetscPrintf(PETSC_COMM_WORLD, "local vector values set\n");

    /* show the vector on standard output */
    if (show_vector)
        VecView(x, PETSC_VIEWER_STDOUT_WORLD);

    /* clean up and finalize PETSc */
    VecDestroy(&x);
    PetscFinalize();
    return 0;
}
