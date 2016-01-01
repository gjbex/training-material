#include <stdlib.h>
#include <CUnit/CUnit.h>

#include <tree_2k.h>
#include <node_2k.h>

#include "query_tests.h"

void test_can_have_points(void) {
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
    const int nr_tests = 4;
    double point_pos[][2] = {
        {0.1, 0.1},
        {1.1, 1.1},
        {-1.1, -1.1},
        {-0.7, 0.3}
    };
    double radius_pos = 0.3;
    double point_neg[][2] = {
        {1.4, 1.1},
        {1.4, 1.1},
        {-1.1, -1.4},
        {-7.0, 0.3}
    };
    double radius_neg = 0.3;
    tree_2k_t *tree;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        status = tree_2k_insert(tree, coords[point_nr], &q[point_nr]);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    for (int test_nr = 0; test_nr < nr_tests; test_nr++) {
        CU_ASSERT_TRUE(node_2k_can_have_points(tree->root,
                                               point_pos[test_nr],
                                               radius_pos));
    }
    for (int test_nr = 0; test_nr < nr_tests; test_nr++) {
        CU_ASSERT_FALSE(node_2k_can_have_points(tree->root,
                                                point_neg[test_nr],
                                                radius_neg));
    }
    tree_2k_free(tree);
}
