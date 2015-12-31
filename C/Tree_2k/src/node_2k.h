/*!
  \file
  \brief Declaration of the node_2k functions.
*/

#ifndef _NODE_2K_HDR_
#define _NODE_2K_HDR_

#include "tree_2k.h"

int node_2k_alloc(node_2k_t **node, tree_2k_t *tree,
                  double *center, double *extent);
void node_2k_free(node_2k_t *node);
int node_2k_insert(node_2k_t *node, int point_id);

#endif
