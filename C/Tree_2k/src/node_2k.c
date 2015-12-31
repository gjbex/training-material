/*!
  \file
  \brief Implementation of the node_2k functionality.

  The functions in this file should not be called by the users of the
  library.
*/

#include <assert.h>
#include <err.h>
#include <stdlib.h>

#include "node_2k.h"

tree_2k_err_t node_2k_init(node_2k_t *node, tree_2k_t *tree,
                           double *center, double *extent);
int get_nr_regions(int rank);

/*!
  \brief Node constructor, will allocate the node itself, all data
         structures required for a node without points inserted into
         it, and initialize all members
  \param node Double dereferenced pointer to the node to be allocated
              and initialized.
  \param tree Address of the tree the node is part off.
  \param center An array of size rank containing the cooridantes of the
         new node's center as double precision numbers,
  \param extent An array of size rank containing the extent for each
         dimension for the new node as double precision numbers,
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_alloc(node_2k_t **node, tree_2k_t *tree,
                            double *center, double *extent) {
    *node = (node_2k_t *) malloc(sizeof(struct node_2k));
    if (*node == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    return node_2k_init(*node, tree, center, extent);
}

/*!
  \brief Node initialization, will allocate the node itself, all data
         structures required for a node without points inserted into
         it, and initialize all members
  \param node Address of the node to be initialized.
  \param tree Tree address the node is part off.
  \param center An array of size rank containing the cooridantes of the
         new node's center as double precision numbers,
  \param extent An array of size rank containing the extent for each
         dimension for the new node as double precision numbers,
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_init(node_2k_t *node, tree_2k_t *tree,
                           double *center, double *extent) {
    assert(tree != NULL);
    assert(center != NULL);
    assert(extent != NULL);
    node->tree = tree;
    node->bucket = (int *) malloc(tree->bucket_size*sizeof(int));
    if (node->bucket == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    node->nr_points = 0;
    node->center = center;
    node->extent = extent;
    node->region = NULL;
    return TREE_2K_SUCCESS;
}

/*!
  \brief Node destructor, will free all memory used by the node, including
         the node itself, and all of its region nodes.
  \param node The node to free.
*/
void node_2k_free(node_2k_t *node) {
    if (node->region != NULL) {
        int nr_regions = get_nr_regions(node->tree->rank);
        for (int region_nr = 0; region_nr < nr_regions; region_nr++) {
            if (node->region[region_nr] != NULL)
                node_2k_free(node->region[region_nr]);
        }
        free(node->region);
    }
    if (node->bucket != NULL)
        free(node->bucket);
    free(node->center);
    free(node->extent);
    free(node);
}

/*!
  \brief Compute the number of regions a node can have base on the rank
  \param rank The rank of the tree.
  \return 2^rank
*/
int get_nr_regions(int rank) {
    int n = 1;
    for (int i = 0; i < rank; i++)
        n *= 2;
    return n;
}

/*!
  \brief Compute the region node's index the given point should be inserted
         into.
  \param node The node to compute the region's index for.
  \param point_id The point's index in the tree's point array.
  \return Integer between 0 and 2^rank - 1 inclusive, index for the node's
                  region array.
*/
int get_region_index(node_2k_t *node, int point_id) {
    int index = 0;
    double *coords = node->tree->coords[point_id];
    for (int i = 0; i < node->tree->rank; i++) {
        index |= (coords[i] < node->center[i] ? 1 : 0) << i;
    }
    return index;
}

/*!
  \brief Computes the extent of a new region node based on the parent
         node's extent.
  \param node Address of the node that will get a new region node with
              the extent to be computed.
  \param extent New extent, rank-sized array.
*/
void get_new_region_extent(node_2k_t *node, double *extent) {
    for (int i = 0; i < node->tree->rank; i++)
        extent[i] = 0.5*node->extent[i];
}

/*!
  \brief Computes the center of a new region node based on the parent
         node's coordinates and extent.
  \param node Address of the node that will get a new region node with
              the center to be computed.
  \param index Index encodes the region.
  \param center New center coordinates, rank-sized array.
*/
void get_new_region_center(node_2k_t *node, int index, double *center) {
    for (int i = 0; i < node->tree->rank; i++)
        if (index & (1 << i))
            center[i] = node->center[i] - 0.5*node->extent[i];
        else
            center[i] = node->center[i] + 0.5*node->extent[i];
}

/*!
  \brief Allocate and initialize a new region node.
  \param node Address of the node to create the new region node in.
  \param index Index encoding the region the new node will represent.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_alloc_region(node_2k_t *node, int index) {
    tree_2k_err_t status;
    double *center, *extent;
    center = (double *) malloc(node->tree->rank*sizeof(double));
    extent = (double *) malloc(node->tree->rank*sizeof(double));
    if (center == NULL || extent == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    get_new_region_center(node, index, center);
    get_new_region_extent(node, extent);
    status = node_2k_alloc(&(node->region[index]), node->tree,
                           center, extent);
    if (status != TREE_2K_SUCCESS)
        return status;
}

/*!
  \brief Split the node into 2^rank nodes, and redistribute the points over
  the new nodes.
  \param node Address of the node to be split.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_split(node_2k_t *node) {
    int nr_regions = get_nr_regions(node->tree->rank);
    node->region = (node_2k_t **) malloc(nr_regions*sizeof(node_2k_t *));
    if (node->region == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    for (int region_nr = 0; region_nr < nr_regions; region_nr++) {
        node->region[region_nr] = NULL;
    }
    for (int i = 0; i < node->nr_points; i++) {
        tree_2k_err_t status;
        int point_id = node->bucket[i];
        int index = get_region_index(node, point_id);
        if (node->region[index] == NULL) {
            status = node_2k_alloc_region(node, index);
            if (status != TREE_2K_SUCCESS)
                return status;
        }
        status = node_2k_insert(node->region[index], point_id);
        if (status != TREE_2K_SUCCESS)
            return status;
    }
    free(node->bucket);
    node->bucket = NULL;
    node->nr_points = 0;
    return TREE_2K_SUCCESS;
}

/*!
  \brief Insert the point with given ID into the node
  \param node Address of the node to insert the point into.
  \param point_id The point's index in the tree's point array.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_insert(node_2k_t *node, int point_id) {
    int index;
    // node has no regions yet
    if (node->region == NULL) {
        // the bucket is not full, so simply insert and return
        if (node->nr_points < node->tree->bucket_size) {
            node->bucket[node->nr_points++] = point_id;
            return TREE_2K_SUCCESS;
        } else {
            // the bucket is full, split the node
            tree_2k_err_t status = node_2k_split(node);
            if (status != TREE_2K_SUCCESS)
                return status;
        }
    }
    // the node has regions, perhaps because it was just split,
    // compute the index for the region to put the piont in, creating
    // a new one if it doesn't exist yet
    index = get_region_index(node, point_id);
    if (node->region[index] == NULL) {
        tree_2k_err_t status = node_2k_alloc_region(node, index);
        if (status != TREE_2K_SUCCESS)
            return status;
    }
    return node_2k_insert(node->region[index], point_id);
}
