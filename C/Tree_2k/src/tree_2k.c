/*!
  \file
  \brief Implementation of the tree_2k functionality.
*/

#include <assert.h>
#include <err.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree_2k.h"
#include "node_2k.h"

tree_2k_err_t tree_2k_validate_params(int rank,
                           double *center, double *extent,
                           int max_points, int bucket_size);
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
    *tree = NULL;
    tree_2k_err_t status = tree_2k_validate_params(rank, center, extent,
                                                   max_points, bucket_size);
    if (status != TREE_2K_SUCCESS)
        return status;
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
    for (int point_nr = 0; point_nr < tree->nr_points; point_nr++)
        free(tree->coords[point_nr]);
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
    tree_2k_err_t status;
    double *new_coords;
    if (!tree_2k_can_store(tree, coords)) {
        return TREE_2K_COORDS_NOT_IN_EXTENT_ERR;
    }
    if (tree->nr_points >= tree->max_points)
        return TREE_2K_CAPACITY_EXCEEDED_ERR;
    tree->coords[tree->nr_points] =
        (double *) malloc(tree->rank*sizeof(double));
    if (tree->coords[tree->nr_points] == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    memcpy(tree->coords[tree->nr_points], coords,
           tree->rank*sizeof(double));
    tree->data[tree->nr_points] = data;
    status = node_2k_insert(tree->root, tree->nr_points);
    if (status != TREE_2K_SUCCESS)
        return status;
    tree->nr_points++;
    return TREE_2K_SUCCESS;
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
  \brief Validate the parameters used to initialize a tree
  \param rank The rank of the points to be stored.
  \param center An array of size rank containing the cooridantes of the
         new node's center as double precision numbers,
  \param extent An array of size rank containing the extent for each
         dimension for the new node as double precision numbers,
  \param max_points The maximum number of points to be stored in the tree.
  \param bucket_size The maximum number of points any node will store
                     before it is split.
  \return TREE_2K_SUCCESS if all parameters are valid, false otherwise
*/
tree_2k_err_t tree_2k_validate_params(int rank,
                           double *center, double *extent,
                           int max_points, int bucket_size) {
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
    return TREE_2K_SUCCESS;
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
    tree->rank = rank;
    tree->bucket_size = bucket_size;
    tree->max_points = max_points;
    tree->data = (void **) malloc(max_points*sizeof(void *));
    tree->coords = (double **) malloc(max_points*sizeof(double *));
    if (tree->data == NULL || tree->coords == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    tree->nr_points = 0;
    node_center = (double *) malloc(tree->rank*sizeof(double));
    node_extent = (double *) malloc(tree->rank*sizeof(double));
    if (node_center == NULL || node_extent == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    memcpy(node_center, center, tree->rank*sizeof(double));
    memcpy(node_extent, extent, tree->rank*sizeof(double));
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

/*!
  \brief Allocate a new query result
  \param query_result Double dereferenced pointer to the query result
  \param max_results The initial capacity of the result list.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t tree_2k_query_result_alloc(tree_2k_query_result_t **query_result,
                                         int max_results) {
    assert(max_results > 0);
    size_t query_size = sizeof(struct tree_2k_query_result *);
    *query_result = (tree_2k_query_result_t *) malloc(query_size);
    if (*query_result == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    (*query_result)->index = (int *) malloc(max_results*sizeof(int));
    if ((*query_result)->index == NULL)
        return TREE_2K_OUT_OF_MEMORY_ERR;
    (*query_result)->nr_results = 0;
    (*query_result)->max_results = max_results;
    return TREE_2K_SUCCESS;
}

/*!
  \brief Free the memory allocated for this query result.
  \param query_result Address of the query result.
*/
void tree_2k_query_result_free(tree_2k_query_result_t *query_result) {
    free(query_result->index);
    free(query_result);
}

/*!
  \brief Store a node index in the list of query results.

  The list will be extended when its maximum capacity is reached.
  \param query_result Address of the query results.
  \param index Point index to add to the list.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t tree_2k_query_result_add(tree_2k_query_result_t *query_result,
                                       int index) {
    if (query_result->nr_results >= query_result->max_results) {
        int new_max = 2*query_result->max_results;
        size_t new_size = new_max*sizeof(int);
        int *new_array = (int *) realloc(query_result->index, new_size);
        if (new_array == NULL)
            return TREE_2K_OUT_OF_MEMORY_ERR;
        query_result->index = new_array;
        query_result->max_results = new_max;
    }
    query_result->index[query_result->nr_results++] = index;
    return TREE_2K_SUCCESS;
}

/*!
  \brief Checks whether a point is within the radius of the query point.
  \param rank Rank of the tree.
  \param p_coord Coordinates as a size rank array of the point to check.
  \param coord Coordinates as a size rank array of the query point.
  \param radius Query radius.
  \return True if the distance between both points is less or equal to
          than radius, false otherwise.
*/
bool tree_2k_is_in_range(int rank, const double *p_coords,
                         const double *coords, double radius) {
    double distance2 = 0.0;
    for (int i = 0; i < rank; i++)
        distance2 += (p_coords[i] - coords[i])*(p_coords[i] - coords[i]);
    return distance2 <= radius*radius;
}

/*!
  \brief Query the tree for points within the given radius from the
         specified point.
  \param tree Address of the tree to query.
  \param coords Coordinates of the query point.
  \param radius Radius to search in.
  \return TREE_2K_SUCCESS if the allocation and initialization succeeded,
          an error code otherwise.
*/
tree_2k_err_t tree_2k_query(tree_2k_t *tree,
                            const double *coords, double radius,
                            tree_2k_query_result_t *query_result) {
    node_2k_list_t *node_list;
    tree_2k_err_t status;
    status = node_2k_list_alloc(&node_list, 10);
    if (status != TREE_2K_SUCCESS)
        return status;
    status = node_2k_query(tree->root, node_list, coords, radius);
    if (status != TREE_2K_SUCCESS)
        return status;
    for (int node_nr = 0; node_nr < node_list->nr_nodes; node_nr++) {
        for (int point_nr = 0; point_nr < node_list->node[node_nr]->nr_points;
                point_nr++) {
            int index = node_list->node[node_nr]->bucket[point_nr];
            if (tree_2k_is_in_range(tree->rank, tree->coords[index],
                                    coords, radius)) {
                tree_2k_query_result_add(query_result, index);
            }
        }
    }
    node_2k_list_free(node_list);
    return TREE_2K_SUCCESS;
}

tree_2k_err_t tree_2k_naive_query_print(tree_2k_t *tree, double *coords,
                                        double radius) {
    for (int point_nr = 0; point_nr < tree->nr_points; point_nr++) {
        if (tree_2k_is_in_range(tree->rank, tree->coords[point_nr],
                                coords, radius)) {
            printf("point %d: (", point_nr);
            for (int i = 0; i < tree->rank; i++)
                printf("%8.4f", tree->coords[point_nr][i]);
            printf(")\n");
        }
    }
}
