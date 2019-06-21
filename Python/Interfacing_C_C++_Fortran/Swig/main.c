#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "cl_params.h"
#include "logistic_map.h"

int main(int argc, char *argv[]) {
    Params params;
    initCL(&params);
    parseCL(&params, &argc, &argv);
    dumpCL(stdout, "# ", &params);
    printf("x_%d(%.3f, %.3f) = %.3f\n", params.steps, params.x0,
           params.r, logistic_map(params.x0, params.r, params.steps));
    finalizeCL(&params);
    return EXIT_SUCCESS;
}

