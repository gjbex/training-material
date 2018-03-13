#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>

#include "fac.h"

void test_fac_0(void);
void test_fac_1(void);
void test_fac_4(void);
void test_fac_too_large(void);

int main(int argc __attribute__((unused)),
         char *argv[] __attribute__((unused))) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");
    CU_pSuite facSuite = CU_add_suite("fac", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());
    CU_add_test(facSuite, "fac(0)", test_fac_0);
    CU_add_test(facSuite, "fac(1)", test_fac_1);
    CU_add_test(facSuite, "fac(4)", test_fac_4);
    CU_add_test(facSuite, "fac(13)", test_fac_too_large);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return EXIT_SUCCESS;
}

void test_fac_0(void) {
    CU_ASSERT_EQUAL(fac(0), 1);
}

void test_fac_1(void) {
    CU_ASSERT_EQUAL(fac(1), 1);
}

void test_fac_4(void) {
    CU_ASSERT_EQUAL(fac(4), 24);
}

void test_fac_too_large(void) {
    CU_ASSERT_EQUAL(fac(13), 6227020800);
}

