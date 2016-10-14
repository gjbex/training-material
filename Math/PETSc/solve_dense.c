#include <petscksp.h>
#include <stdlib.h>

static char help[] = "demonstrates solving a system of linear equations.\n";

int main(int argc, char *argv[]) {
    Mat A;
    Vec b, x, y;
    KSP ksp;
    PetscInt n = 10, local_min_row, local_max_row, nr_local_rows,
             local_vec_size, nr_iters;
    PetscScalar *local_values;
    int *row_idxs, *col_idxs;
    int i, nr_values, rank;
    PetscReal local_start, minus_one = -1.0, norm;

    /* initialize PETSc, and read options */
    PetscInitialize(&argc, &argv, (char *) 0, help);
    PetscOptionsGetInt(NULL, "-n", &n, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* Intialize the matrix, all values are computed and sotred locally */
    MatCreateDense(PETSC_COMM_WORLD, PETSC_DECIDE, PETSC_DECIDE, n, n,
                   NULL, &A);
    MatSetFromOptions(A);
    MatGetOwnershipRange(A, &local_min_row, &local_max_row);
    nr_local_rows = local_max_row - local_min_row;
    nr_values = n*nr_local_rows;
    local_values = (PetscScalar *) malloc(nr_values*sizeof(PetscScalar));
    row_idxs = (int *) malloc(nr_local_rows*sizeof(int));
    col_idxs = (int *) malloc(n*sizeof(int));
    if (local_values == NULL || row_idxs == NULL || col_idxs == NULL) {
    }
    for (i = 0; i < nr_local_rows; i++)
        row_idxs[i] = local_min_row + i;
    for (i = 0; i < n; i++)
        col_idxs[i] = i;
    local_start = 100.0*rank + local_min_row*n + 1;
    for (i = 0; i < nr_values; i++)
        local_values[i] = local_start + i + ((double) rand())/RAND_MAX;
    MatSetValues(A, nr_local_rows, row_idxs, n, col_idxs, local_values,
                 INSERT_VALUES);
    MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);
    free(local_values);
    free(row_idxs);
    free(col_idxs);

    /* initialize vector b */
    VecCreate(PETSC_COMM_WORLD, &b);
    VecSetSizes(b, PETSC_DECIDE, n);
    VecSetFromOptions(b);
    VecGetLocalSize(b, &local_vec_size);
    VecGetArray(b, &local_values);
    for (i = 0; i < local_vec_size; i++)
        local_values[i] = rank + ((double) rand())/RAND_MAX;
    VecAssemblyBegin(b);
    VecAssemblyEnd(b);
     
    /* initialize vector x */
    VecCreate(PETSC_COMM_WORLD, &x);
    VecSetSizes(x, PETSC_DECIDE, n);
    VecSetFromOptions(x);

    /* initialize the solver */
    KSPCreate(PETSC_COMM_WORLD, &ksp);
    KSPSetOperators(ksp, A, A);
    KSPSetFromOptions(ksp);

    /* selve the system of linear equations A.x = b */
    KSPSolve(ksp, b, x);
    KSPGetIterationNumber(ksp, &nr_iters);
    PetscPrintf(PETSC_COMM_WORLD, "KSP required %d iterations\n", nr_iters);

    /* verify solution */
    VecCreate(PETSC_COMM_WORLD, &y);
    VecSetSizes(y, PETSC_DECIDE, n);
    VecSetFromOptions(y);
    MatMult(A, x, y);
    VecAXPY(y, minus_one, b);
    VecNorm(y, NORM_2, &norm);
    PetscPrintf(PETSC_COMM_WORLD, "||A.x - b|| = %.3e\n", norm);

    /* destroy data structures and finalize */
    KSPDestroy(&ksp);
    MatDestroy(&A);
    VecDestroy(&b);
    VecDestroy(&x);
    PetscFinalize();

    return 0;
}
