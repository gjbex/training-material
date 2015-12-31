#include <err.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>

#include "init_tests.h"
#include "insert_tests.h"

int main(int argc, char *argv[]) {
    int status = CU_initialize_registry();
    CU_pSuite init_suite, insert_suite;
    if (status != CUE_SUCCESS)
        errx(status, "CUnit registry initialization failed");
    init_suite = CU_add_suite("init", NULL, NULL);
    CU_add_test(init_suite, "basic tree allocation",
                &test_tree_alloc);
    CU_add_test(init_suite, "tree allocation rank failure",
                &test_tree_alloc_rank_0);
    CU_add_test(init_suite, "tree allocation invalid extent failure",
                &test_tree_alloc_invalid_extent);
    insert_suite = CU_add_suite("insert", NULL, NULL);
    CU_add_test(insert_suite, "single insert",
                &test_single_insert);
    CU_add_test(insert_suite, "multiple inserts, no split",
                &test_multiple_insert_no_split);
    CU_add_test(insert_suite, "multiple inserts, with split",
                &test_multiple_insert_with_split);
    CU_add_test(insert_suite, "failed insert, not in extent",
                &test_failed_insert);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return EXIT_SUCCESS;
}
