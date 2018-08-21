#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>

int initialize();
int cleanup();
void test_sum();
void test_product();

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(1, "failed to initialize test registry");
    CU_pSuite suite = CU_add_suite("array", initialize, cleanup);
    if (CU_get_error() != CUE_SUCCESS)
        errx(2, "failed to add test suite");
    CU_add_test(suite, "sum", test_sum);
    CU_add_test(suite, "product", test_product);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}

static const int size = 5;
static int *array;

int initialize() {
#ifdef VERBOSE
    fprintf(stderr, "running initialize\n");
#endif
    array = (int *) malloc(size*sizeof(int));
    if (!array)
        return 1;
    for (int i = 0; i < size; i++)
        array[i] = i + 1;
    return 0;
}

int cleanup() {
#ifdef VERBOSE
    fprintf(stderr, "running cleanup\n");
#endif
    free(array);
    return 0;
}

void test_sum() {
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += array[i];
    CU_ASSERT_EQUAL(sum, 15);
}

void test_product() {
    int prod = 1;
    for (int i = 0; i < size; i++)
        prod *= array[i];
    CU_ASSERT_EQUAL(prod, 120);
}

