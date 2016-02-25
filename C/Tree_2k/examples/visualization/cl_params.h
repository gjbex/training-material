#ifndef CL_PARAMS_HDR
#define CL_PARAMS_HDR

#include <stdio.h>

typedef struct {
	int rank;
	int nr_points;
	int bucket_size;
	int verbose;
} Params;

void initCL(Params *params);
void parseCL(Params *params, int *argc, char **argv[]);
void parseFileCL(Params *params, char *fileName);
void dumpCL(FILE *fp, char prefix[], Params *params);
void finalizeCL(Params *params);
void printHelpCL(FILE *fp);

#endif