/*!
  \file
  \brief Implementation of the tree_2k functionality.
*/

#include <assert.h>
#include <err.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree_2k.h"
#include "node_2k.h"

tree_2k_err_t tree_2k_init(tree_2k_t *tree, int rank,
                           double *center, double *extent,
                           int max_points, int bucket_size);
bool is_valid_extent(int rank, double *extent);

/*!
  \brief Tree constructor, will allocate the tree itself, all data
         structures required for a tree without points inserted into
         it, and initialize all members
  \param tree Double dereferenced pointer to a tree_2k_t that will be
              allocated and initialized.
  \param rank The rank of the points to be stored.
  \param center An array of size rank containing the cooridantes of the
         new node's center as double precision numbers,
  \param extent An array of size rank containing the extent for each
         dimension for the new node as double precision numbers,
  \param max_points The maximum number of points to be stored in the tree.
  \param bucket_size The maximum number of points any node will store
                     before it is split.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t tree_2k_alloc(tree_2k_t **tree, int rank,
                            double *center, double *extent,
                            int max_points, int bucket_size) {
    *tree = (tree_2k_t *) malloc(sizeof(struct tree_2k));
    if (*tree == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    return tree_2k_init(*tree, rank, center, extent,
                        max_points, bucket_size);
}

/*!
  \brief Tree destructor, will free all memory used by the tree, including
         the tree itself.
  \param tree The address of the tree to free.
*/
void tree_2k_free(tree_2k_t *tree) {
    for (int i = 0; i < tree->nr_points; i++)
        free(tree->coords[i]);
    free(tree->data);
    free(tree->coords);
    node_2k_free(tree->root);
    free(tree);
}

/*!
  \brief Check whether the given coordinates can be stored in the tree.

  A point can only be stored in the tree when its coordinates fall into
  the tree's extent.
  \param tree Address of the tree to check whether it can store the given
              point.
  \param coords A size rank array with the coordinates to tesst.
  \return True when the coordinates can be stored, false otherwise.
*/
bool tree_2k_can_store(tree_2k_t *tree, double *coords) {
    for (int i = 0; i < tree->rank; i++)
        if (coords[i] < tree->root->center[i] - tree->root->extent[i] ||
            tree->root->center[i] + tree->root->extent[i] < coords[i])
            return false;
    return true;
}

/*!
  \brief Insert a point with given coordinates and (optionally)
         associated data in the tree.
  \param tree Address of the tree to store the data in.
  \param coords An array of size rank that represents the point's
                coordinates
  \param data A pointer to data to be associated with the point, may be
              NULL if that is not necessary.  Note that memory management
              is up to the caller, data is not copied, and not freed.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t tree_2k_insert(tree_2k_t *tree, double *coords, void *data) {
    double *new_coords;
    if (!tree_2k_can_store(tree, coords)) {
        return TREE_2K_COORDS_NOT_IN_EXTENT_ERR;
    }
    if (tree->nr_points >= tree->max_points) {
        return TREE_2K_CAPACITY_EXCEEDED_ERR;
    } else {
        tree->coords[tree->nr_points] =
            (double *) malloc(tree->rank*sizeof(double));
        if (tree->coords[tree->nr_points] == NULL)
            return TREE_2K_OUT_OF_MEMORY_ERR;
        for (int i = 0; i < tree->rank; i++)
            tree->coords[tree->nr_points][i] = coords[i];
        tree->data[tree->nr_points] = data;
        return node_2k_insert(tree->root, tree->nr_points++);
    }
}

/*!
  \brief Return the tree's rank.
  \param tree Address of the tree to retrieve the rank of.
  \return The rank of the tree.
*/
int tree_2k_get_rank(tree_2k_t *tree) {
    return tree->rank;
}

/*!
  \brief Return the total number of points currently stored in the tree.
  \param tree Address of the tree to retrieve the number of points of.
  \return The number of points in the tree.
*/
int tree_2k_get_nr_points(tree_2k_t *tree) {
    return tree->nr_points;
}

/*!
  \brief Retrieves the coordinates of the point specified by the point ID.
  \param tree Address of the tree to fetch the coordinates from.
  \param point_id Point ID to retrieve the cooridnates for.
  \return Constant array of size rank, or NULL is the given point ID is
          not valid.
*/
const double *tree_2k_get_coords(tree_2k_t *tree, int point_id) {
    if (0 <= point_id && point_id < tree->nr_points)
        return tree->coords[point_id];
    else
        return NULL;
}

/*!
  \brief Retrieves the data of the point specified by the point ID.
  \param tree Address of the tree to fetch the data from.
  \param point_id Point ID to retrieve the data for.
  \return Address of the data, or NULL is the given point ID is not valid.
*/
void *tree_2k_get_data(tree_2k_t *tree, int point_id) {
    if (0 <= point_id && point_id < tree->nr_points)
        return tree->data[point_id];
    else
        return NULL;
}

/*!
  \brief Tree initializer, will allocate the tree itself, all data
         structures required for a tree without points inserted into
         it, and initialize all members
  \param tree Address of the tree to be initialized.
  \param rank The rank of the points to be stored.
  \param center An array of size rank containing the cooridantes of the
         new node's center as double precision numbers,
  \param extent An array of size rank containing the extent for each
         dimension for the new node as double precision numbers,
  \param max_points The maximum number of points to be stored in the tree.
  \param bucket_size The maximum number of points any node will store
                     before it is split.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t tree_2k_init(tree_2k_t *tree, int rank,
                           double *center, double *extent,
                           int max_points, int bucket_size) {
    double *node_center, *node_extent;
    if (rank <= 0)
        return TREE_2K_INVALID_RANK_ERR;
    if (center == NULL)
        return TREE_2K_CENTER_IS_NULL_ERR;
    if (extent == NULL)
        return TREE_2K_EXTENT_IS_NULL_ERR;
    if (!is_valid_extent(rank, extent))
        return TREE_2K_INVALID_EXTENT_ERR;
    if (max_points <= 0)
        return TREE_2K_INVALID_MAX_POINT_ERR;
    if (bucket_size <= 0)
        return TREE_2K_INVALID_BUCKET_SIZE_ERR;
    tree->rank = rank;
    tree->bucket_size = bucket_size;
    tree->max_points = max_points;
    tree->data = (void **) malloc(sizeof(void *));
    tree->coords = (double **) malloc(max_points*sizeof(double *));
    if (tree->data == NULL || tree->coords == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    tree->nr_points = 0;
    node_center = (double *) malloc(tree->rank*sizeof(double));
    node_extent = (double *) malloc(tree->rank*sizeof(double));
    if (node_center == NULL || node_extent == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    for (int i = 0; i < rank; i++) {
        node_center[i] = center[i];
        node_extent[i] = extent[i];
    }
    return node_2k_alloc(&(tree->root), tree, node_center, node_extent);
}

/*!
  \brief Checks whether the given extent is valid.

  An extent is valid when all its components are strictly positive.
  \param rank The rank of the tree.
  \param extent An array of size rank, storing double precision numbers
*/
bool  is_valid_extent(int rank, double *extent) {
    for (int i = 0; i < rank; i++)
        if (extent[i] <= 0.0)
            return false;
    return true;
}

/*!
  \brief Compute an estimate for the number of query result.

  The assumption is that the number of query results will be proportional to
  the ratio between the total volume represented by the tree and that of
  query.
  \param tree Address of the tree to query.
  \param radius The query's radius.
  \return An estimate for the number of query results.
*/
int tree_2k_estimate_result_size(tree_2k_t *tree, double radius) {
    double total_volume = 1.0, query_volume = 1.0;
    for (int i = 0; i < tree->rank; i++) {
        total_volume *= tree->root->extent[i];
        query_volume *= radius;
    }
    return tree->bucket_size  +
        ((int) ceil(tree->nr_points*query_volume/total_volume));
}

tree_2k_err_t tree_2k_query(tree_2k_t *tree, double *coords, double radius,
                            tree_2k_query_result_t *query_result) {

    return TREE_2K_SUCCESS;
}
