#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <tree_2k.h>
#include "cl_params.h"

void tree_spatial_dims_alloc(Params params, double **center,
        double **extent);
void tree_spatial_dims_free(double *center, double *extent);
double insert_points(tree_2k_t *tree, int nr_points);
double query_points(tree_2k_t *tree, double radius, int *nr_results,
                    int verbose);
double naive_query_points(tree_2k_t *tree, double radius, int *nr_results,
                          int verbose);

int main(int argc, char *argv[]) {
    tree_2k_t *tree;
    tree_2k_err_t status;
    double *center, *extent;
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
    printf("nr_points bucket_size i_time");
    printf(" radius nr_results q_time");
    printf(" n_nr_results n_q_time\n");
    for (int point_nr = params.delta_nr_points;
            point_nr <= params.max_nr_points;
            point_nr += params.delta_nr_points) {
        double i_time = insert_points(tree, params.delta_nr_points);
        for (double radius = params.delta_radius;
                radius <= params.max_radius + 0.1*params.delta_radius;
                radius += params.delta_radius) {
            double q_time = 0.0, n_q_time = 0.0;
            int nr_results = 0, n_nr_results = 0;
            for (int iter_nr = 0; iter_nr < params.nr_iters; iter_nr++) {
                q_time += query_points(tree, radius, &nr_results,
                                      params.verbose);
                n_q_time += naive_query_points(tree, radius, &n_nr_results,
                                              params.verbose);
            }
            printf("%d %d %.6lf %.2lf %d %.6lf %d %.6lf\n",
                   point_nr, tree->bucket_size, i_time, radius, nr_results,
                   q_time/params.nr_iters, n_nr_results,
                   n_q_time/params.nr_iters);
        }
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

bool is_in_circle(int rank, double *coords) {
    double d2 = 0.0;
    for (int i = 0; i < rank; i++)
        d2 += coords[i]*coords[i];
    return d2 < 1.0;
}

double compute_time(struct timeval start_time, struct timeval end_time) {
    return (end_time.tv_sec - start_time.tv_sec) +
        1.0e-6*(end_time.tv_usec - start_time.tv_usec);
}

double insert_points(tree_2k_t *tree, int nr_points) {
    tree_2k_err_t status;
    const int rank = tree_2k_get_rank(tree);
    struct timeval start_time, end_time;
    int point_nr = 0;
    double *coords = (double *) malloc(rank*sizeof(double)*nr_points);
    if (coords == NULL)
        errx(EXIT_FAILURE, "can not allocate coords");
    while (point_nr < nr_points) {
        int offset = point_nr*rank;
        for (int i = 0; i < rank; i++)
            coords[offset + i] = 2.0*((double) rand())/RAND_MAX - 1.0;
        if (is_in_circle(rank, &(coords[offset])))
            point_nr++;
    }
    gettimeofday(&start_time, NULL);
    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        status = tree_2k_insert(tree, &(coords[point_nr*rank]), NULL);
        if (status != TREE_2K_SUCCESS)
            errx(EXIT_FAILURE, "can not insert point in tree: %d", status);
    }
    gettimeofday(&end_time, NULL);
    free(coords);
    return compute_time(start_time, end_time);
}

double query_tree(tree_2k_t *tree, double radius, int *nr_results,
                  tree_2k_err_t (*func) (tree_2k_t *, const double *,
                                         double, tree_2k_query_result_t *),
                  int verbose) {
    struct timeval start_time, end_time;
    double *coords, *c_coords;
    tree_2k_err_t status;
    tree_2k_query_result_t *query_result;
    coords = (double *) malloc(tree_2k_get_rank(tree)*sizeof(double));
    c_coords = (double *) malloc(tree_2k_get_rank(tree)*sizeof(double));
    if (coords == NULL || c_coords == NULL)
        errx(EXIT_FAILURE, "can not allocate coords");
    for (int i = 0; i < tree_2k_get_rank(tree); i++)
        coords[i] = c_coords[i] = 0.0;
    status = tree_2k_query_result_alloc(&query_result,
                                        tree_2k_get_nr_points(tree));
    if (status != TREE_2K_SUCCESS)
        errx(EXIT_FAILURE, "can not allocate query results");
    gettimeofday(&start_time, NULL);
    status = func(tree, coords, radius, query_result);
    if (status != TREE_2K_SUCCESS)
        errx(EXIT_FAILURE, "query failed");
    *nr_results = query_result->nr_results;
    for (int result_nr = 0; result_nr < query_result->nr_results;
            result_nr++) {
        const double *p_coords = tree_2k_get_coords(
                tree, query_result->index[result_nr]
        );
        for (int i = 0; i < tree_2k_get_rank(tree); i++)
            c_coords[i] += p_coords[i];
    }
    gettimeofday(&end_time, NULL);
    if (verbose) {
        fprintf(stderr, "center of mass = ");
        for (int i = 0; i < tree_2k_get_rank(tree); i++)
            fprintf(stderr, "%10.5f", c_coords[i]);
        fprintf(stderr, "\n");
    }
    tree_2k_query_result_free(query_result);
    free(coords);
    free(c_coords);
    return compute_time(start_time, end_time);
}

double query_points(tree_2k_t *tree, double radius, int *nr_results,
                    int verbose) {
    return query_tree(tree, radius, nr_results, &tree_2k_query, verbose);
}

double naive_query_points(tree_2k_t *tree, double radius, int *nr_results,
                          int verbose) {
    return query_tree(tree, radius, nr_results, &tree_2k_naive_query,
                      verbose);
}
