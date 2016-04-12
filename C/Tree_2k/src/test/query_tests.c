#include <stdlib.h>
#include <CUnit/CUnit.h>

#include <tree_2k.h>
#include <node_2k.h>

#include "query_tests.h"

void test_can_have_points(void) {
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
    tree_2k_free(&tree);
}

void expected_query_result(tree_2k_t *tree, double *coords, double radius,
                           int *nr_results, int **results) {
    *nr_results = 0;
    *results = (int *) malloc(tree->nr_points*sizeof(int));
    for (int point_nr = 0; point_nr < tree->nr_points; point_nr++) {
        double d2 = 0.0;
        for (int i = 0; i < tree->rank; i++)
            d2 += (tree->coords[point_nr][i] - coords[i])*
                (tree->coords[point_nr][i] - coords[i]);
        if (d2 <= radius*radius)
            (*results)[(*nr_results)++] = point_nr;
    }
}

void test_query_success(void) {
    const int nr_points = 9;
    tree_2k_err_t status;
    const int rank = 2, max_points = 10, bucket_size = 2;
    double center[] = {0.0, 0.0};
    double extent[] = {1.0, 1.0};
    double query[2], radius;
    int nr_results, *results;
    tree_2k_query_result_t *query_result;
    tree_2k_t *tree;
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
    query[0] = 0.3;
    query[1] = 0.3;
    radius = 0.5;
    tree_2k_query_result_alloc(&query_result, nr_points);
    status = tree_2k_query(tree, query, radius, query_result);
    CU_ASSERT_EQUAL_FATAL(status, TREE_2K_SUCCESS);
    CU_ASSERT_PTR_NOT_NULL_FATAL(query_result->index);
    expected_query_result(tree, query, radius, &nr_results, &results);
    CU_ASSERT_EQUAL(query_result->nr_results, nr_results);
    tree_2k_query_result_free(&query_result);
    tree_2k_free(&tree);
    free(results);
}
