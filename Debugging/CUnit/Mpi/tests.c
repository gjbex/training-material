#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <mpi.h>

void test_mpi_reduce(void);

int main(int argc __attribute((unused)),
         char *argv[] __attribute((unused))) {
    MPI_Init(NULL, NULL);
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");
    CU_pSuite facSuite = CU_add_suite("fac", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());
    CU_add_test(facSuite, "mpi_reduce", test_mpi_reduce);
    CU_basic_run_tests();
    CU_cleanup_registry();
    MPI_Finalize();
    return EXIT_SUCCESS;
}

void test_mpi_reduce(void) {
    int root = 0;
    int rank, send_buff, recv_buff;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    send_buff = rank;
    MPI_Reduce(&send_buff, &recv_buff, 1, MPI_INT, MPI_SUM, root,
               MPI_COMM_WORLD);
    if (rank == root) {
        int size, target = 0, i;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        for (i = 0; i < size; i++)
            target += i;
        CU_ASSERT_EQUAL(recv_buff, target);
    }
}
