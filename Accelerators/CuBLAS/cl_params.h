#ifndef CL_PARAMS_HDR
#define CL_PARAMS_HDR

#include <stdbool.h>
#include <stdio.h>

typedef struct {
	int N;
	int nr_iters;
	bool skip_gpu_xt;
	bool skip_cpu;
} Params;

void initCL(Params *params);
void parseCL(Params *params, int *argc, char **argv[]);
void parseFileCL(Params *params, char *fileName);
void dumpCL(FILE *fp, char prefix[], Params *params);
void finalizeCL(Params *params);
void printHelpCL(FILE *fp);

#endif