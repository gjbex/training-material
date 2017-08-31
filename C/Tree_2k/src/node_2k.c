/*!
  \file
  \brief Implementation of the node_2k functionality.

  The functions in this file should not be called by the users of the
  library.
*/

#include <assert.h>
#include <err.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "node_2k.h"

tree_2k_err_t node_2k_init(node_2k_t *node, tree_2k_t *tree,
                           double *center, double *extent);

/*!
  \brief Node constructor, will allocate the node itself, all data
         structures required for a node without points inserted into
         it, and initialize all members
  \param node Double dereferenced pointer to the node to be allocated
              and initialized.
  \param tree Address of the tree the node is part off.
  \param center An array of size rank containing the coordinates of the
                new node's center as double precision numbers,
  \param extent An array of size rank containing the extent for each
                dimension for the new node as double precision numbers,
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_alloc(node_2k_t **node, tree_2k_t *tree,
                            double *center, double *extent) {
    *node = (node_2k_t *) malloc(sizeof(struct node_2k));
    if (*node == NULL) {
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[TREE_2K_OUT_OF_MEMORY_ERR]);
        return TREE_2K_OUT_OF_MEMORY_ERR;
    }
    tree_2k_err_t status = node_2k_init(*node, tree, center, extent);
    if (status != TREE_2K_SUCCESS)
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[status]);
    return status;
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
    if (node->bucket == NULL) {
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[TREE_2K_OUT_OF_MEMORY_ERR]);
        return TREE_2K_OUT_OF_MEMORY_ERR;
    }
    node->nr_points = 0;
    node->center = center;
    node->extent = extent;
    node->region = NULL;
    return TREE_2K_SUCCESS;
}

/*!
  \brief Node destructor, will free all memory used by the node, including
         the node itself, and all of its region nodes.
  \param node The address of the node to free.
*/
void node_2k_free(node_2k_t **node) {
    if ((*node)->region != NULL) {
        for (int region_nr = 0; region_nr < (*node)->tree->nr_regions;
                region_nr++)
            if ((*node)->region[region_nr] != NULL)
                node_2k_free(&((*node)->region[region_nr]));
        free((*node)->region);
    }
    if ((*node)->bucket != NULL)
        free((*node)->bucket);
    free((*node)->center);
    free((*node)->extent);
    free(*node);
    node = NULL;
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
    if (center == NULL || extent == NULL) {
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[TREE_2K_OUT_OF_MEMORY_ERR]);
        return TREE_2K_OUT_OF_MEMORY_ERR;
    }
    get_new_region_center(node, index, center);
    get_new_region_extent(node, extent);
    status = node_2k_alloc(&(node->region[index]), node->tree,
                           center, extent);
    if (status != TREE_2K_SUCCESS)
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[status]);
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
    int nr_regions = node->tree->nr_regions;
    node->region = (node_2k_t **) malloc(nr_regions*sizeof(node_2k_t *));
    if (node->region == NULL) {
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[TREE_2K_OUT_OF_MEMORY_ERR]);
        return TREE_2K_OUT_OF_MEMORY_ERR;
    }
    for (int region_nr = 0; region_nr < nr_regions; region_nr++)
        node->region[region_nr] = NULL;
    for (int i = 0; i < node->nr_points; i++) {
        tree_2k_err_t status;
        int point_id = node->bucket[i];
        int index = get_region_index(node, point_id);
        if (node->region[index] == NULL) {
            status = node_2k_alloc_region(node, index);
            if (status != TREE_2K_SUCCESS) {
                warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                        tree_2k_err_msg[status]);
                return status;
            }
        }
        status = node_2k_insert(node->region[index], point_id);
        if (status != TREE_2K_SUCCESS) {
            warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                    tree_2k_err_msg[status]);
            return status;
        }
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
            if (status != TREE_2K_SUCCESS) {
                warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                        tree_2k_err_msg[status]);
                return status;
            }
        }
    }
    // the node has regions, perhaps because it was just split,
    // compute the index for the region to put the piont in, creating
    // a new one if it doesn't exist yet
    index = get_region_index(node, point_id);
    if (node->region[index] == NULL) {
        tree_2k_err_t status = node_2k_alloc_region(node, index);
        if (status != TREE_2K_SUCCESS) {
            warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                    tree_2k_err_msg[status]);
            return status;
        }
    }
    tree_2k_err_t status =  node_2k_insert(node->region[index], point_id);
    if (status != TREE_2K_SUCCESS)
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[status]);
    return status;
}

/*!
  \brief Check whether the given point can have points in this node
         within the given radius.

  Note: this may produce false positives.

  \param node Address of the node to check for.
  \param coords An array of size rank that represent the query point.
  \param radius The query's radius.
  \return True if the node can have points within the given radius, false
          otherwise.
*/
bool node_2k_can_have_points(node_2k_t *node, const double *coords,
                             double radius) {
    for (int i = 0; i < node->tree->rank; i++)
        if (fabs(node->center[i] - coords[i]) > radius + node->extent[i])
            return false;
    return true;
}

/*!
  \brief Checks whether a node is a leaf in the tree.
  \param node Address of the node to check
  \return True if the node has no region nodes, false otherwise.
*/
bool node_2k_is_leaf(node_2k_t *node) {
    return node->region == NULL;
}

/*!
  \brief Allocate a new node list.
  \param node_list Double dereferenced pointer to the list of nodes.
  \param max_nodes The initial capacity of the list.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_list_alloc(node_2k_list_t **node_list,
                                 int max_nodes) {
    assert(max_nodes > 0);
    *node_list = (node_2k_list_t *) malloc(sizeof(struct node_2k_list));
    if (*node_list == NULL) {
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[TREE_2K_OUT_OF_MEMORY_ERR]);
        return TREE_2K_OUT_OF_MEMORY_ERR;
    }
    size_t list_size = max_nodes*sizeof(node_2k_t *);
    (*node_list)->node = (node_2k_t **) malloc(list_size);
    if ((*node_list)->node == NULL) {
        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[TREE_2K_OUT_OF_MEMORY_ERR]);
        return TREE_2K_OUT_OF_MEMORY_ERR;
    }
    (*node_list)->nr_nodes = 0;
    (*node_list)->max_nodes = max_nodes;
    return TREE_2K_SUCCESS;
}

/*!
  \brief Free the memory allocated for this node list.
  \param node_list Pointer to address of a node list
*/
void node_2k_list_free(node_2k_list_t **node_list) {
    free((*node_list)->node);
    free(*node_list);
    node_list = NULL;
}

/*!
  \brief Store a node address in the list of nodes.

  The list will be extended when its maximum capacity is reached.
  \param node_list Address of the list of nodes.
  \param node Node address to add to the list.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_list_add(node_2k_list_t *node_list,
                               node_2k_t *node) {
    if (node_list->nr_nodes >= node_list->max_nodes) {
        int new_max = 2*node_list->max_nodes;
        size_t new_size = new_max*sizeof(node_2k_t *);
        node_2k_t **new_array = (node_2k_t **) realloc(node_list->node,
                                                       new_size);
        if (new_array == NULL) {
            warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                    tree_2k_err_msg[TREE_2K_OUT_OF_MEMORY_ERR]);
            return TREE_2K_OUT_OF_MEMORY_ERR;
        }
        node_list->node = new_array;
        node_list->max_nodes = new_max;
    }
    node_list->node[node_list->nr_nodes++] = node;
    return TREE_2K_SUCCESS;
}

/*!
  \brief Recursively go down in region nodes, returning a list of any node
         that could have points within the radius of the query point.
  \param node Address of the node to query.
  \param query_result Address of the node_2k_list of nodes that could
                      satisfy the query.
  \param coords An array of size rank that represent the query point.
  \param radius The query's radius.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_query(node_2k_t *node, node_2k_list_t *query_result,
                            const double *coords, double radius) {
    if (node_2k_can_have_points(node, coords, radius)) {
        if (node_2k_is_leaf(node)) {
            node_2k_list_add(query_result, node);
        } else {
            for (int region_nr = 0; region_nr < node->tree->nr_regions;
                    region_nr++) {
                if (node->region[region_nr] != NULL) {
                    tree_2k_err_t status;
                    status = node_2k_query(node->region[region_nr],
                                           query_result, coords, radius);
                    if (status != TREE_2K_SUCCESS) {
                        warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                                tree_2k_err_msg[status]);
                        return status;
                    }
                }
            }
        }
    }
    return TREE_2K_SUCCESS;
}

/*!
  \brief Walks the tree downwoard from the specified node in post order,
         first processing regions, then the node itself using the specifed
         function and its argument.
  \param node Address of the starting node.
  \param f Function to call.
  \param x Argument for the function.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t node_2k_walk(node_2k_t *node,
                           int (*f) (node_2k_t *, void *),
                           void *x) {
    if (!node_2k_is_leaf(node)) {
        for (int region_nr = 0; region_nr < node->tree->nr_regions;
                region_nr++) {
            if (node->region[region_nr] != NULL) {
                tree_2k_err_t status = node_2k_walk(node->region[region_nr],
                                                    f, x);
                if (status != TREE_2K_SUCCESS) {
                    warnx(TREE_2K_ERR_FMT, __FILE__, __func__, __LINE__,
                            tree_2k_err_msg[status]);
                    return status;
                }
            }
        }
    }
    int err = f(node, x);
    if (err != TREE_2K_SUCCESS) {
        warnx(TREE_2K_UDF_ERR_FMT, __FILE__, __func__, __LINE__,
                tree_2k_err_msg[TREE_2K_UDF_FAIL_ERR], err);
        return TREE_2K_UDF_FAIL_ERR;
    } else {
        return TREE_2K_SUCCESS;
    }
}
