#include <CUnit/CUnit.h>

#include <tree_2k.h>

#include "init_tests.h"

void test_tree_alloc(void) {
    const double PREC = 1.0e-12;
    const int rank = 2, max_points = 10, bucket_size = 1;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    tree_2k_t *tree;
    int status = tree_2k_alloc(&tree, rank, center, extent,
                               max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    CU_ASSERT_EQUAL(tree->rank, rank);
    CU_ASSERT_EQUAL(tree->max_points, max_points);
    CU_ASSERT_EQUAL(tree->bucket_size, bucket_size);
    CU_ASSERT_PTR_NOT_NULL(tree->data);
    CU_ASSERT_PTR_NOT_NULL(tree->coords);
    CU_ASSERT_PTR_NOT_NULL_FATAL(tree->root);
    CU_ASSERT_PTR_NOT_NULL(tree->root->bucket);
    CU_ASSERT_PTR_NOT_NULL_FATAL(tree->root->center);
    for (int i = 0; i < rank; i++)
        CU_ASSERT_DOUBLE_EQUAL(tree->root->center[i], center[i], PREC);
    CU_ASSERT_PTR_NOT_NULL_FATAL(tree->root->extent);
    for (int i = 0; i < rank; i++)
        CU_ASSERT_DOUBLE_EQUAL(tree->root->extent[i], extent[i], PREC);
    tree_2k_free(&tree);
}

void test_tree_alloc_rank_0(void) {
    const int rank = 0, max_points = 10, bucket_size = 1;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    tree_2k_t *tree;
    tree_2k_err_t status = tree_2k_alloc(&tree, rank, center, extent,
                                         max_points, bucket_size);
    CU_ASSERT_EQUAL(status, TREE_2K_INVALID_RANK_ERR);
}

void test_tree_alloc_invalid_extent(void) {
    const int rank = 2, max_points = 10, bucket_size = 1;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 0.0};
    tree_2k_t *tree;
    tree_2k_err_t status = tree_2k_alloc(&tree, rank, center, extent,
                                         max_points, bucket_size);
    CU_ASSERT_EQUAL(status, TREE_2K_INVALID_EXTENT_ERR);
}
