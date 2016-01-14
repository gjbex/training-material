#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <tree_2k.h>
#include <tree_2k_utils.h>
#include "cl_params.h"

void tree_spatial_dims_alloc(Params params, double **center,
        double **extent);
void tree_spatial_dims_free(double *center, double *extent);
void insert_points(tree_2k_t *tree, int nr_points);

int main(int argc, char *argv[]) {
    tree_2k_t *tree;
    tree_2k_err_t status;
    tree_2k_stats_t stats;
    double *center, *extent;
    size_t tree_size, data_size;
    Params params;
    initCL(&params);
    parseCL(&params, &argc, &argv);
    if (params.verbose)
        dumpCL(stderr, "# ", &params);
    tree_spatial_dims_alloc(params, &center, &extent);
    status = tree_2k_alloc(&tree, params.rank, center, extent,
            params.max_nr_points, params.bucket_size);
    if (status != TREE_2K_SUCCESS)
        errx(EXIT_FAILURE, "can not allocate tree: %d", status);
    printf("nr_points nr_nodes nr_leafs avg_points stddev_oints");
    printf(" coord_size total_size\n");
    for (int point_nr = params.delta_nr_points;
            point_nr <= params.max_nr_points;
            point_nr += params.delta_nr_points) {
        insert_points(tree, params.delta_nr_points);
        tree_2k_compute_stats(tree, &stats);
        tree_2k_sizeof(tree, &tree_size);
        tree_2k_data_sizeof(tree, &data_size);
        printf("%d %d %d %.2lf %.3lf %lu %lu\n",
                tree_2k_get_nr_points(tree), stats.nr_nodes, stats.nr_leafs,
                stats.avg_nr_points, stats.stddev_nr_points,
                (unsigned long) data_size, (unsigned long) tree_size);
    }
    finalizeCL(&params);
    tree_2k_free(tree);
    tree_spatial_dims_free(center, extent);
    return EXIT_SUCCESS;
}

void tree_spatial_dims_alloc(Params params, double **center,
        double **extent) {
    *center = (double *) malloc(params.rank*sizeof(double));
    *extent = (double *) malloc(params.rank*sizeof(double));
    if (*center == NULL || *extent == NULL)
        errx(EXIT_FAILURE, "can not allocate center and extent"); 
    for (int i = 0; i < params.rank; i++) {
        (*center)[i] = 0.0;
        (*extent)[i] = 1.0;
    }
}

void tree_spatial_dims_free(double *center, double *extent) {
    free(center);
    free(extent);
}

void insert_points(tree_2k_t *tree, int nr_points) {
    tree_2k_err_t status;
    const int rank = tree_2k_get_rank(tree);
    double *coords = (double *) malloc(rank*sizeof(double));
    if (coords == NULL)
        errx(EXIT_FAILURE, "can not allocate coords");
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        for (int i = 0; i < rank; i++)
            coords[i] = 2.0*((double) rand())/RAND_MAX - 1.0;
        status = tree_2k_insert(tree, coords, NULL);
        if (status != TREE_2K_SUCCESS)
            errx(EXIT_FAILURE, "can not insert point in tree: %d", status);
    }
    free(coords);
}
