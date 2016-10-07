#include <petscvec.h>

static char help[] = "Demonstates vector norm.\n";

int main(int argc, char **argv) {
    Vec x;
    PetscReal norm;
    PetscInt n = 20;
    PetscScalar one = 1.0;

    /* initialize PETSc, and get command line option for vector size */
    PetscInitialize(&argc, &argv, (char *) 0, help);
    PetscPrintf(PETSC_COMM_WORLD, "initializatoin complete\n");
    PetscOptionsGetInt(NULL, "-n", &n, NULL);
    PetscPrintf(PETSC_COMM_WORLD, "vector length = %d\n", (int) n);

    /* create and initialize vector */
    VecCreate(PETSC_COMM_WORLD, &x);
    VecSetSizes(x, PETSC_DECIDE, n);
    /* only required for strided norm */
    VecSetBlockSize(x, 2);
    VecSetFromOptions(x);
    VecSet(x, one);
    PetscPrintf(PETSC_COMM_WORLD, "vector created\n");

    /* compute and print the vector's 2-norm */
    VecNorm(x, NORM_1, &norm);
    PetscPrintf(PETSC_COMM_WORLD, "norm = %.2e\n", (double) norm);

    /* compute and print the vector's strided 2-norm, the stride will be
     * 2, i.e., the vector's block size.
     */
    VecStrideNorm(x, 0, NORM_1, &norm);
    PetscPrintf(PETSC_COMM_WORLD, "strided norm = %.2e\n", (double) norm);

    /* destroy data structures, and finalize PETSc */
    VecDestroy(&x);
    PetscFinalize();

    return 0;
}
