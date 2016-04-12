#include <stdlib.h>
#include <CUnit/CUnit.h>

#include <tree_2k.h>

#include "insert_tests.h"

void test_single_insert(void) {
    const int nr_points = 1;
    tree_2k_err_t status;
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
    tree_2k_free(&tree);
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
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        status = tree_2k_insert(tree, coords[point_nr], &q[point_nr]);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    CU_ASSERT_EQUAL_FATAL(tree->nr_points, nr_points);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        for (int i = 0; i < rank; i++) {
            CU_ASSERT_DOUBLE_EQUAL(tree->coords[point_nr][i],
                                   coords[point_nr][i], PREC);
        }
        CU_ASSERT_EQUAL(*((int *) tree->data[point_nr]), q[point_nr]);
    }
    CU_ASSERT_EQUAL_FATAL(tree->root->nr_points, nr_points);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        CU_ASSERT_EQUAL(tree->root->bucket[point_nr], point_nr);
    }
    CU_ASSERT_PTR_NULL(tree->root->region);
    tree_2k_free(&tree);
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
    double new_center[][2] = {
        {+0.5, +0.5},
        {-0.5, +0.5},
        {+0.5, -0.5}
    };
    double new_extent[] = {0.5, 0.5};
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        status = tree_2k_insert(tree, coords[point_nr], &q[point_nr]);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    CU_ASSERT_EQUAL_FATAL(tree->nr_points, nr_points);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        for (int i = 0; i < rank; i++) {
            CU_ASSERT_DOUBLE_EQUAL(tree->coords[point_nr][i],
                                   coords[point_nr][i], PREC);
        }
        CU_ASSERT_EQUAL(*((int *) tree->data[point_nr]), q[point_nr]);
    }
    CU_ASSERT_EQUAL(tree->root->nr_points, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(tree->root->region);
    for (int region_nr = 0; region_nr < 3; region_nr++) {
        CU_ASSERT_PTR_NOT_NULL_FATAL(tree->root->region[region_nr]);
        CU_ASSERT_EQUAL(tree->root->region[region_nr]->nr_points, 1);
        CU_ASSERT_EQUAL(tree->root->region[region_nr]->bucket[0],
                        region_content[region_nr]);
        for (int i = 0; i < tree->rank; i++) {
            CU_ASSERT_DOUBLE_EQUAL(tree->root->region[region_nr]->center[i],
                                   new_center[region_nr][i], PREC); 
            CU_ASSERT_DOUBLE_EQUAL(tree->root->region[region_nr]->extent[i],
                                   new_extent[i], PREC); 
        }
    }
    CU_ASSERT_PTR_NULL(tree->root->region[3]);
    tree_2k_free(&tree);
}

void test_failed_insert(void) {
    tree_2k_err_t status;
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
    tree_2k_free(&tree);
    free(q);
}

void test_increase_capacity_insert(void) {
    const int nr_points = 30;
    tree_2k_err_t status;
    const double PREC = 1.0e-12;
    const int rank = 2, max_points = 10, bucket_size = 5;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    double coords[2];
    int *data;
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        coords[0] = ((double) point_nr)/nr_points;
        coords[1] = ((double) point_nr)/nr_points;
        data = (int *) malloc(sizeof(int));
        *data = point_nr;
        status = tree_2k_insert(tree, coords, data);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    CU_ASSERT_EQUAL_FATAL(tree->nr_points, nr_points);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        coords[0] = ((double) point_nr)/nr_points;
        coords[1] = ((double) point_nr)/nr_points;
        for (int i = 0; i < rank; i++) {
            CU_ASSERT_DOUBLE_EQUAL(tree->coords[point_nr][i],
                                   coords[i], PREC);
        }
        CU_ASSERT_EQUAL(*((int *) tree->data[point_nr]), point_nr);
    }
    for (int point_nr = 0; point_nr < nr_points; point_nr++)
        free(tree->data[point_nr]);
    tree_2k_free(&tree);
}
