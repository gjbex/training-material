#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

#include <tree_2k.h>
#include <tree_2k_utils.h>

#include "cl_params.h"

void tree_spatial_dims_alloc(Params params, double **center,
                             double **extent);
void tree_spatial_dims_free(double *center, double *extent);
void insert_points(tree_2k_t *tree, Params params);

int main(int argc, char *argv[]) {
    tree_2k_err_t status;
    double *center, *extent;
    Params params;
    initCL(&params);
    parseCL(&params, &argc, &argv);
    if (params.verbose)
        dumpCL(stderr, "# ", &params);
    tree_spatial_dims_alloc(params, &center, &extent);
    tree_2k_t * tree;
    status = tree_2k_alloc(&tree, params.rank, center, extent,
                           params.nr_points, params.bucket_size);
    if (status != TREE_2K_SUCCESS)
        errx(EXIT_FAILURE, "can not allocate tree");
    insert_points(tree, params);
    status = tree_2k_fwrite(tree, stdout);
    if (status != TREE_2K_SUCCESS)
        errx(EXIT_FAILURE, "tree write failed");
    tree_2k_free(&tree);
    tree_spatial_dims_free(center, extent);
    finalizeCL(&params);
    return EXIT_SUCCESS;
}

void tree_spatial_dims_alloc(Params params, double **center,
                             double **extent) {
    *center = (double *) malloc(params.rank*sizeof(double));
    *extent = (double *) malloc(params.rank*sizeof(double));
    if (*center == NULL || *extent == NULL)
        errx(EXIT_FAILURE, "can not allocate center or extent");
    for (int i = 0; i < params.rank; i++) {
        (*center)[i] = 0.0;
        (*extent)[i] = 1.0;
    }
}

void tree_spatial_dims_free(double *center, double *extent) {
    free(center);
    free(extent);
}

void insert_points(tree_2k_t *tree, Params params) {
    double *coords;
    gsl_rng *rng;
    gsl_rng_env_setup();
    rng = gsl_rng_alloc(gsl_rng_default);
    if ((coords = (double *) malloc(params.rank*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can not allocate coords");
    for (int point_nr = 0; point_nr < params.nr_points; point_nr++) {
        for (int i = 0; i < params.rank; i++)
            coords[i] = 2.0*gsl_rng_uniform(rng) - 1.0;
        tree_2k_err_t status = tree_2k_insert(tree, coords, NULL);
        if (status != TREE_2K_SUCCESS)
            errx(EXIT_FAILURE, "failed to insert point %d", point_nr);
    }
    gsl_rng_free(rng);
}
