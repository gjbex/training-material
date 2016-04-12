/*!
  \file
  \brief Declaration of the node_2k functions.
*/

#ifndef _NODE_2K_HDR_
#define _NODE_2K_HDR_

#include "tree_2k.h"

/*!
  \brief Data structure to represent a list of nodes
*/
typedef struct node_2k_list {
    /*! Elements of the list */
    node_2k_t **node;
    /*! Current number of elements in the list */
    int nr_nodes;
    /*! Maximum number of elements in the list */
    int max_nodes;
} node_2k_list_t;

tree_2k_err_t node_2k_list_alloc(node_2k_list_t **node_list,
                                 int max_nodes);
void node_2k_list_free(node_2k_list_t **node_list);

tree_2k_err_t node_2k_alloc(node_2k_t **node, tree_2k_t *tree,
                            double *center, double *extent);
void node_2k_free(node_2k_t **node);
tree_2k_err_t node_2k_insert(node_2k_t *node, int point_id);
bool node_2k_can_have_points(node_2k_t *node, const double *coords,
                             double radius);
bool node_2k_is_leaf(node_2k_t *node);
tree_2k_err_t node_2k_query(node_2k_t *node, node_2k_list_t *query_result,
                            const double *coords, double radius);
tree_2k_err_t node_2k_walk(node_2k_t *node,
                           int (*f) (node_2k_t *, void *),
                           void *x);

#endif
