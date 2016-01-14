#include <err.h>
#include <math.h>
#include <stdlib.h>

#include "tree_2k_utils.h"
#include "node_2k.h"

/*!
  \brief Write the node's center and extent to the specified file pointer
  \param node Address of the node to process.
  \param fptr File pointer to write to.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
int node_2k_fwrite(node_2k_t *node, void *fptr) {
    if (node_2k_is_leaf(node)) {
        FILE *fp = (FILE *) fptr;
        const int rank = tree_2k_get_rank(node->tree);
        fprintf(fp, "%.15le", node->center[0]);
        for (int i = 1; i < rank; i++)
            fprintf(fp, " %.15le", node->center[i]);
        for (int i = 0; i < rank; i++)
            fprintf(fp, " %.15le", node->extent[i]);
        fprintf(fp, "\n");
    }
    return TREE_2K_SUCCESS;
}

/*!
  \brief Write the center and extent of all the tree's nodes to the
         specified file pointer
  \param tree Address of the tree to write out
  \param fptr File pointer to write to.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t tree_2k_fwrite(tree_2k_t *tree, FILE *fp) {
    tree_2k_err_t status;
    fprintf(fp, "# tree structure\n");
    status = tree_2k_walk(tree, &node_2k_fwrite, fp);
    if (status != TREE_2K_SUCCESS)
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
              tree_2k_err_msg[status]);
    fprintf(fp, "# points\n");
    for (int point_nr = 0; point_nr < tree_2k_get_nr_points(tree);
            point_nr++) {
        fprintf(fp, "%.15le", tree->coords[point_nr][0]);
        for (int i = 1; i < tree_2k_get_rank(tree); i++)
            fprintf(fp, " %.15le", tree->coords[point_nr][i]);
        fprintf(fp, "\n");
    }
    return status;
}

int node_2k_update_stats(node_2k_t *node, void *x) {
    tree_2k_stats_t *stats = (tree_2k_stats_t *) x;
    stats->nr_nodes++;
    if (node_2k_is_leaf(node)) {
        stats->nr_leafs++;
        stats->sum_nr_points += node->nr_points;
        stats->sum_nr_points_2 += node->nr_points*node->nr_points;
    }
    return TREE_2K_SUCCESS;
}

tree_2k_err_t tree_2k_compute_stats(tree_2k_t *tree,
                                    tree_2k_stats_t *stats) {
    stats->nr_nodes = stats->nr_leafs = 0;
    stats->sum_nr_points = stats->sum_nr_points_2 = 0;
    stats->avg_nr_points = stats->stddev_nr_points = 0.0;
    tree_2k_walk(tree, &node_2k_update_stats, stats);
    stats->avg_nr_points = ((double) stats->sum_nr_points)/stats->nr_leafs;
    stats->stddev_nr_points = sqrt(
            ((double) stats->sum_nr_points_2)/stats->nr_leafs -
            stats->avg_nr_points*stats->avg_nr_points
    );
    return TREE_2K_SUCCESS;
}

tree_2k_err_t tree_2k_data_min_sizeof(tree_2k_t *tree, size_t *total_size) {
    *total_size = 0;
    /* minimal size of the array holding the coordinate array addresses */
    *total_size += tree->nr_points*sizeof(double *);
    /* minimal size of all the arrays holding the actual coordinates */
    *total_size += tree->nr_points*tree_2k_get_rank(tree)*sizeof(double);
    /* minimal size of the data array, so not the actual data */
    *total_size += tree->nr_points*sizeof(void *);
    return TREE_2K_SUCCESS;
}

tree_2k_err_t tree_2k_data_sizeof(tree_2k_t *tree, size_t *total_size) {
    *total_size = 0;
    /* size of the array holding the coordinate array addresses */
    *total_size += tree->max_points*sizeof(double *);
    /* size of all the arrays holding the actual coordinates */
    *total_size += tree->max_points*tree_2k_get_rank(tree)*sizeof(double);
    /* size of the data array, so not the actual data */
    *total_size += tree->max_points*sizeof(void *);
    return TREE_2K_SUCCESS;
}

tree_2k_err_t tree_2k_sizeof(tree_2k_t *tree, size_t *total_size) {
    tree_2k_err_t status;
    tree_2k_stats_t stats;
    size_t data_size;
    *total_size = 0;
    status = tree_2k_compute_stats(tree, &stats);
    if (status != TREE_2K_SUCCESS) {
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[status]);
        return status;
    }
    /* size of the tree itself */
    *total_size += sizeof(tree_2k_t);
    /* size of the actual data stored, i.e., both coordiantes and
       addresses of data */
    status = tree_2k_data_sizeof(tree, &data_size);
    if (status != TREE_2K_SUCCESS) {
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[status]);
        return status;
    }
    *total_size += data_size;
    /* size of all nodes */
    *total_size += stats.nr_nodes*sizeof(node_2k_t);
    /* size of all the buckets, so only in leaf nodes */
    *total_size += stats.nr_leafs*tree->bucket_size*sizeof(int);
    /* size of the reginn array in each non-leaf node */
    *total_size += tree->nr_regions*sizeof(node_2k_t *);
    return TREE_2K_SUCCESS;
}
