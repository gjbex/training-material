/*!
  \file
  \brief Declaration of the tree_2k utility functions.
*/

#ifndef _TREE_2K_UTIL_HDR_
#define _TREE_2K_UTIL_HDR_

#include <stdio.h>

#include "tree_2k.h"

/*!
  \brief Internal type to collect statistics on a tree_2k
*/
typedef struct tree_2k_stats {
    /*! \brief Total number of nodes in the tree. */
    int nr_nodes;
    /*! \brief Total number of leaf nodes in the tree. */
    int nr_leafs;
    /*! \brief Average number of points per node. */
    double avg_nr_points;
    /*! \brief Standard deviation of number of points per node. */
    double stddev_nr_points;
    /*! \brief Sum of number of node points. */
    int sum_nr_points;
    /*! \brief Sum of squares of number of node points. */
    int sum_nr_points_2;
} tree_2k_stats_t;

tree_2k_err_t tree_2k_fwrite(tree_2k_t *tree, FILE *fp);
tree_2k_err_t tree_2k_compute_stats(tree_2k_t *tree,
                                    tree_2k_stats_t *stats);

#endif
