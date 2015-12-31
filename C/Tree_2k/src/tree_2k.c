/*!
  \file
  \brief Implementation of the tree_2k functionality.
*/

#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree_2k.h"
#include "node_2k.h"

tree_2k_err_t tree_2k_init(tree_2k_t *tree, int rank,
                           double *center, double *extent,
                           int max_points, int bucket_size);
int is_valid_extent(int rank, double *extent);

/*!
  \brief Tree constructor, will allocate the tree itself, all data
         structures required for a tree without points inserted into
         it, and initialize all members
  \param tree Address of a pointer to a tree_2k_t.
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
  \brief Tree initializer, will allocate the tree itself, all data
         structures required for a tree without points inserted into
         it, and initialize all members
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
    int i;
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
    for (i = 0; i < rank; i++) {
        node_center[i] = center[i];
        node_extent[i] = extent[i];
    }
    return node_2k_alloc(&(tree->root), tree, node_center, node_extent);
}

/*!
  \brief Tree destructor, will free all memory used by the tree, including
         the tree itself.
  \param tree The tree to free.
*/
void tree_2k_free(tree_2k_t *tree) {
    int i;
    for (i = 0; i < tree->nr_points; i++)
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
  \param tree The tree to check for.
  \param coords A size rank array with the coordinates to tesst.
  \return True when the coordinates can be stored, false otherwise.
*/
int tree_2k_can_store(tree_2k_t *tree, double *coords) {
    int i;
    for (i = 0; i < tree->rank; i++)
        if (coords[i] < tree->root->center[i] - tree->root->extent[i] ||
            tree->root->center[i] + tree->root->extent[i] < coords[i])
            return FALSE;
    return TRUE;
}

/*!
  \brief Insert a point with given coordinates and (optionally)
         associated data in the tree.
  \param tree Tree to store the data in.
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
        int i;
        tree->coords[tree->nr_points] =
            (double *) malloc(tree->rank*sizeof(double));
        if (tree->coords[tree->nr_points] == NULL)
            return TREE_2K_OUT_OF_MEMORY_ERR;
        for (i = 0; i < tree->rank; i++)
            tree->coords[tree->nr_points][i] = coords[i];
        tree->data[tree->nr_points] = data;
        return node_2k_insert(tree->root, tree->nr_points++);
    }
}

/*!
  \brief Checks whether the given extent is valid.

  An extent is valid when all its components are strictly positive.
  \param rank The rank of the tree.
  \param extent An array of size rank, storing double precision numbers
*/
int is_valid_extent(int rank, double *extent) {
    int i;
    for (i = 0; i < rank; i++)
        if (extent[i] <= 0.0)
            return FALSE;
    return TRUE;
}
