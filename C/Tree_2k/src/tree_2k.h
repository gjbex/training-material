/*!
  \file
  \brief Declaration of the tree_2k data structures and functions.

  \mainpage tree_2k library
 
  This is a library that implements a tree data structure
  to store and query spatial data.
  It is similar to a quadtree, but works for any specified rank. 
*/

#ifndef _TREE_2K_HDR_
#define _TREE_2K_HDR_

#include <stdbool.h>

#include "tree_2k_err.h"

/*!
  \brief Data structure for the nodes in the tree.

  This data structure should not be used directly by users of the library.
*/
typedef struct node_2k {
    /*! Tree this node is part of. */
    struct tree_2k *tree;
    /*! Node's bucket, contains the indices of the points stored by
        this node, will be NULL if node is split. */
    int *bucket;
    /*! Number of points in this node, may be zero if the node
        has regions. */
    int nr_points;
    /*! The node's center. */
    double *center;
    /*! The node's extent. */
    double *extent;
    /*! Array containing the node's region nodes, NULL if node is not
        split.  Note that only populated regions are non-NULL. */
    struct node_2k **region;
} node_2k_t;

/*!
  \brief Data structure to store points and associated data, and query.
*/
typedef struct tree_2k {
    /*! Tree rank. */
    int rank; 
    /*! Number of regions per node */
    int nr_regions;
    /*! Number of points currently in the tree. */
    int nr_points;
    /*! Maximum number of points the tree can store. */
    int max_points;
    /*! Size of the nodes' buckets. */
    int bucket_size;
    /*! Data associated with points. */
    void **data;
    /*! Coordinates of the points in the tree. */
    double **coords;
    /*! Root node for the tree. */
    node_2k_t *root;
} tree_2k_t;

/*!
  \brief Data structure to represent a list of nodes indices
*/
typedef struct tree_2k_query_result {
    /*! Elements of the list */
    int *index;
    /*! Current number of elements in the list */
    int nr_results;
    /*! Maximum number of elements in the list */
    int max_results;
} tree_2k_query_result_t;

tree_2k_err_t tree_2k_query_result_alloc(tree_2k_query_result_t **query_result,
                                         int max_results);
void tree_2k_query_result_free(tree_2k_query_result_t **query_result);

tree_2k_err_t tree_2k_alloc(tree_2k_t **tree, int rank,
                            double *center, double *extent,
                            int max_points, int bucket_size);
void tree_2k_free(tree_2k_t **tree);
bool tree_2k_can_store(tree_2k_t *tree, double *coords);
tree_2k_err_t tree_2k_insert(tree_2k_t *tree, double *coords, void *data);
int tree_2k_get_rank(tree_2k_t *tree);
int tree_2k_get_nr_points(tree_2k_t *tree);
const double *tree_2k_get_coords(tree_2k_t *tree, int i);
void *tree_2k_get_data(tree_2k_t *tree, int point_id);
tree_2k_err_t tree_2k_query(tree_2k_t *tree,
                            const double *coords, double radius,
                            tree_2k_query_result_t *query_result);
tree_2k_err_t tree_2k_naive_query(tree_2k_t *tree,
                                  const double *coords, double radius,
                                  tree_2k_query_result_t *query_result);
tree_2k_err_t tree_2k_walk(tree_2k_t *node,
                           int (*f) (node_2k_t *, void *),
                           void *x);

#endif
