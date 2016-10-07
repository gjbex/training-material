#include <petscksp.h>
#include <stdlib.h>

static char help[] = "demonstrates solving a set of linear equations.\n";

int main(int argc, char *argv[]) {
    Mat A;
    Vec b, x;
    PetscInt n = 10, local_min_row, local_max_row, nr_local_rows;
    PetscScalar *local_values;
    int *row_idxs, *col_idxs;
    int i, nr_values, rank;

    /* initialize PETSc, and read options */
    PetscInitialize(&argc, &argv, (char *) 0, help);
    PetscOptionsGetInt(NULL, "-n", &n, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* Intialize the matrix */
    MatCreateDense(PETSC_COMM_WORLD, PETSC_DECIDE, PETSC_DECIDE, n, n,
                   NULL, &A);
    MatSetFromOptions(A);
    MatGetOwnershipRange(A, &local_min_row, &local_max_row);
    printf("rank %d: from %d to %d\n", rank, local_min_row, local_max_row);
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
    for (i = 0; i < nr_values; i++)
        local_values[i] = ((double) rand())/RAND_MAX;
    MatSetValues(A, nr_local_rows, row_idxs, n, col_idxs, local_values,
                 INSERT_VALUES);
    MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);

    /* destroy data structures and finalize */
    free(local_values);
    free(row_idxs);
    free(col_idxs);
    MatDestroy(&A);
    PetscFinalize();

    return 0;
}
