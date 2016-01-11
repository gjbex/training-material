#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "cl_params.h"
#include "cl_params_aux.h"

#define MAX_CL_OPT_LEN 128
#define MAX_CL_LINE_LEN 1024

void initCL(Params *params) {
	params->rank = 2;
	params->max_nr_points = 1000;
	params->delta_nr_points = 100;
	params->bucket_size = 10;
	params->verbose = 0;
}

void parseCL(Params *params, int *argc, char **argv[]) {
	char *argv_str;
	int i = 1;
	while (i < *argc) {
		 if (!strncmp((*argv)[i], "-?", 3)) {
			printHelpCL(stderr);
			finalizeCL(params);
			exit(EXIT_SUCCESS);
		}
		if (!strncmp((*argv)[i], "-rank", 6)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-rank' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->rank = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-max_nr_points", 15)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-max_nr_points' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->max_nr_points = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-delta_nr_points", 17)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-delta_nr_points' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->delta_nr_points = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-bucket_size", 13)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-bucket_size' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->bucket_size = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-verbose", 9)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-verbose' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->verbose = atoi(argv_str);
			i++;
			continue;
		}
		break;
	}
	if (i > 1) {
		(*argv)[i - 1] = (*argv)[0];
		*argv = &((*argv)[i - 1]);
		*argc -= (i - 1);
	}
}

void parseFileCL(Params *params, char *fileName) {
	char line_str[MAX_CL_LINE_LEN];
	char argv_str[MAX_CL_LINE_LEN];
	FILE *fp;
	if (!(fp = fopen(fileName, "r"))) {
		fprintf(stderr, "### error: can not open file '%s'\n", fileName);
		exit(EXIT_CL_FILE_OPEN_FAIL);
	}
	while (fgets(line_str, MAX_CL_LINE_LEN, fp)) {
		if (isCommentCL(line_str)) continue;
		if (isEmptyLineCL(line_str)) continue;
		if (sscanf(line_str, "rank = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-rank' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->rank = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "max_nr_points = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-max_nr_points' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->max_nr_points = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "delta_nr_points = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-delta_nr_points' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->delta_nr_points = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "bucket_size = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-bucket_size' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->bucket_size = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "verbose = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-verbose' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->verbose = atoi(argv_str);
			continue;
		}
		fprintf(stderr, "### warning, line can not be parsed: '%s'\n", line_str);
	}
	fclose(fp);
}

void dumpCL(FILE *fp, char prefix[], Params *params) {
	fprintf(fp, "%srank = %d\n", prefix, params->rank);
	fprintf(fp, "%smax_nr_points = %d\n", prefix, params->max_nr_points);
	fprintf(fp, "%sdelta_nr_points = %d\n", prefix, params->delta_nr_points);
	fprintf(fp, "%sbucket_size = %d\n", prefix, params->bucket_size);
	fprintf(fp, "%sverbose = %d\n", prefix, params->verbose);
}

void finalizeCL(Params *params) {
}

void printHelpCL(FILE *fp) {
	fprintf(fp, "  -rank <integer>\n  -max_nr_points <integer>\n  -delta_nr_points <integer>\n  -bucket_size <integer>\n  -verbose <integer>\n  -?: print this message");
}