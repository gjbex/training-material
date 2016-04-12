#include <stdlib.h>
#include <CUnit/CUnit.h>

#include <tree_2k.h>
#include <node_2k.h>

#include "walk_tests.h"

int count_points(node_2k_t *node, void *x) {
    *((int *) x) += node->nr_points;
    return TREE_2K_SUCCESS;
}

void test_count_walk(void) {
    const int nr_points = 9;
    tree_2k_err_t status;
    const int rank = 2, max_points = 10, bucket_size = 1;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    tree_2k_t *tree;
    int counted_points = 0;
    status = tree_2k_alloc(&tree, rank, center, extent,
                           max_points, bucket_size);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        int i = point_nr/3;
        int j = point_nr % 3;
        double coords[] = {0.1 + (i - 1)*0.3, -0.1 + (j - 1)*0.25};
        status = tree_2k_insert(tree, coords, NULL);
        CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    }
    CU_ASSERT_EQUAL(tree_2k_get_nr_points(tree), nr_points);
    status = tree_2k_walk(tree, &count_points, &counted_points);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    CU_ASSERT_EQUAL(counted_points, tree_2k_get_nr_points(tree));
    tree_2k_free(&tree);
}
