#include <CUnit/CUnit.h>

#include <tree_2k.h>

#include "accessor_tests.h"

void test_basic_accessors(void) {
    const int nr_points = 3;
    tree_2k_err_t status;
    const int rank = 2, max_points = 10, bucket_size = 5;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    double coords[][2] = {
        {-0.2, +0.3},
        {+0.5, -0.4},
        {+0.1, +0.7}
    };
    int q[] = {-1, 0, +1};
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    CU_ASSERT_EQUAL(tree_2k_get_rank(tree), rank);
    for (int i = 0; i < nr_points; i++) {
        status = tree_2k_insert(tree, coords[i], &q[i]);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    CU_ASSERT_EQUAL(tree_2k_get_nr_points(tree), nr_points);
    tree_2k_free(&tree);
}

void test_data_accessors(void) {
    const int nr_points = 3;
    tree_2k_err_t status;
    const int rank = 2, max_points = 10, bucket_size = 5;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    double coords[][2] = {
        {-0.2, +0.3},
        {+0.5, -0.4},
        {+0.1, +0.7}
    };
    int q[] = {-1, 0, +1};
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    for (int i = 0; i < nr_points; i++) {
        status = tree_2k_insert(tree, coords[i], &q[i]);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    CU_ASSERT_EQUAL_FATAL(tree_2k_get_nr_points(tree), nr_points);
    for (int point_nr = 0; point_nr < tree_2k_get_nr_points(tree);
            point_nr++) {
        const double *p_coords = tree_2k_get_coords(tree, point_nr);
        CU_ASSERT_PTR_NOT_NULL_FATAL(p_coords);
        for (int i = 0; i < tree_2k_get_rank(tree); i++)
            CU_ASSERT_EQUAL(p_coords[i], coords[point_nr][i]);
    }
    tree_2k_free(&tree);
}

void test_data_access_fail(void) {
    const int nr_points = 3;
    tree_2k_err_t status;
    const int rank = 2, max_points = 10, bucket_size = 5;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    double coords[][2] = {
        {-0.2, +0.3},
        {+0.5, -0.4},
        {+0.1, +0.7}
    };
    int q[] = {-1, 0, +1};
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    for (int i = 0; i < nr_points; i++) {
        status = tree_2k_insert(tree, coords[i], &q[i]);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    CU_ASSERT_EQUAL_FATAL(tree_2k_get_nr_points(tree), nr_points);
    CU_ASSERT_PTR_NULL(tree_2k_get_coords(tree, 3));
    CU_ASSERT_PTR_NULL(tree_2k_get_data(tree, 3));
    tree_2k_free(&tree);
}
