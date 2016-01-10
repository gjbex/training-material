#include <err.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void add_init_suite(void);
void add_insert_suite(void);
void add_accessor_suite(void);
void add_query_suite(void);
void add_walk_suite(void);

int main(int argc, char *argv[]) {
    int status = CU_initialize_registry();
    if (status != CUE_SUCCESS)
        errx(status, "CUnit registry initialization failed");
    add_init_suite();
    add_insert_suite();
    add_accessor_suite();
    add_query_suite();
    add_walk_suite();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return EXIT_SUCCESS;
}

#include "init_tests.h"
void add_init_suite(void) {
    CU_pSuite suite = CU_add_suite("init", NULL, NULL);
    CU_add_test(suite, "basic tree allocation",
                &test_tree_alloc);
    CU_add_test(suite, "tree allocation rank failure",
                &test_tree_alloc_rank_0);
    CU_add_test(suite, "tree allocation invalid extent failure",
                &test_tree_alloc_invalid_extent);
}

#include "insert_tests.h"
void add_insert_suite(void) {
    CU_pSuite suite = CU_add_suite("insert", NULL, NULL);
    CU_add_test(suite, "single insert",
                &test_single_insert);
    CU_add_test(suite, "multiple inserts, no split",
                &test_multiple_insert_no_split);
    CU_add_test(suite, "multiple inserts, with split",
                &test_multiple_insert_with_split);
    CU_add_test(suite, "failed insert, not in extent",
                &test_failed_insert);
    CU_add_test(suite, "capacity increase",
                &test_increase_capacity_insert);
}

#include "accessor_tests.h"
void add_accessor_suite(void) {
    CU_pSuite suite = CU_add_suite("accessors", NULL, NULL);
    CU_add_test(suite, "basic accessors",
                &test_basic_accessors);
    CU_add_test(suite, "data accessors",
                &test_data_accessors);
    CU_add_test(suite, "data access fail",
                &test_data_access_fail);
}

#include "query_tests.h"
void add_query_suite(void) {
    CU_pSuite suite = CU_add_suite("queries", NULL, NULL);
    CU_add_test(suite, "can have point",
                &test_can_have_points);
    CU_add_test(suite, "succesful query",
                &test_query_success);
}

#include "walk_tests.h"
void add_walk_suite(void) {
    CU_pSuite suite = CU_add_suite("walks", NULL, NULL);
    CU_add_test(suite, "counts points",
                &test_count_walk);
}
