#include <stdlib.h>
#include <CUnit/CUnit.h>

#include <tree_2k.h>

#include "insert_tests.h"

void test_single_insert(void) {
    const int nr_points = 1;
    tree_2k_err_t status;
    const double PREC = 1.0e-12;
    const int rank = 2, max_points = 10, bucket_size = 1;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    double coords[] = {-0.2, 0.3};
    int *q = (int *) malloc(sizeof(int));
    *q = 1;
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    status = tree_2k_insert(tree, coords, q);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    CU_ASSERT_EQUAL_FATAL(tree->nr_points, nr_points);
    for (int i = 0; i < rank; i++) {
        CU_ASSERT_EQUAL(tree->coords[0][i], coords[i]);
    }
    CU_ASSERT_EQUAL(*((int *) tree->data[0]), *q);
    CU_ASSERT_EQUAL_FATAL(tree->root->nr_points, nr_points);
    CU_ASSERT_EQUAL(tree->root->bucket[0], 0);
    CU_ASSERT_PTR_NULL(tree->root->region);
    tree_2k_free(tree);
    free(q);
}

void test_multiple_insert_no_split(void) {
    const int nr_points = 3;
    tree_2k_err_t status;
    const double PREC = 1.0e-12;
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
    CU_ASSERT_EQUAL_FATAL(tree->nr_points, nr_points);
    for (int i = 0; i < nr_points; i++) {
        for (int j = 0; j < rank; j++) {
            CU_ASSERT_EQUAL(tree->coords[i][j], coords[i][j]);
        }
        CU_ASSERT_EQUAL(*((int *) tree->data[i]), q[i]);
    }
    CU_ASSERT_EQUAL_FATAL(tree->root->nr_points, nr_points);
    for (int i = 0; i < nr_points; i++) {
        CU_ASSERT_EQUAL(tree->root->bucket[i], i);
    }
    CU_ASSERT_PTR_NULL(tree->root->region);
    tree_2k_free(tree);
}

void test_multiple_insert_with_split(void) {
    const int nr_points = 3;
    tree_2k_err_t status;
    const double PREC = 1.0e-12;
    const int rank = 2, max_points = 10, bucket_size = 1;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    double coords[][2] = {
        {-0.2, +0.3},
        {+0.5, -0.4},
        {+0.1, +0.7}
    };
    int q[] = {-1, 0, +1};
    int region_content[] = {2, 0, 1};
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    for (int i = 0; i < nr_points; i++) {
        status = tree_2k_insert(tree, coords[i], &q[i]);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    CU_ASSERT_EQUAL_FATAL(tree->nr_points, nr_points);
    for (int i = 0; i < nr_points; i++) {
        for (int j = 0; j < rank; j++) {
            CU_ASSERT_EQUAL(tree->coords[i][j], coords[i][j]);
        }
        CU_ASSERT_EQUAL(*((int *) tree->data[i]), q[i]);
    }
    CU_ASSERT_EQUAL(tree->root->nr_points, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(tree->root->region);
    for (int region_nr = 0; region_nr < 3; region_nr++) {
        CU_ASSERT_PTR_NOT_NULL_FATAL(tree->root->region[region_nr]);
        CU_ASSERT_EQUAL(tree->root->region[region_nr]->nr_points, 1);
        CU_ASSERT_EQUAL(tree->root->region[region_nr]->bucket[0],
                        region_content[region_nr]);
    }
    CU_ASSERT_PTR_NULL(tree->root->region[3]);
    tree_2k_free(tree);
}
void test_failed_insert(void) {
    tree_2k_err_t status;
    const double PREC = 1.0e-12;
    const int rank = 2, max_points = 10, bucket_size = 1;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    double coords[] = {-0.2, 3.0};
    int *q = (int *) malloc(sizeof(int));
    *q = 1;
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    status = tree_2k_insert(tree, coords, q);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_COORDS_NOT_IN_EXTENT_ERR);
    tree_2k_free(tree);
}
