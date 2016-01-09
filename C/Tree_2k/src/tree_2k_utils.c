#include <err.h>
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
