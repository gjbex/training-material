#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "cl_params.h"
#include "cl_params_aux.h"

#define MAX_CL_OPT_LEN 128
#define MAX_CL_LINE_LEN 1024

void initCL(Params *params) {
	params->x0 = 0.5;
	params->r = 3.2;
	params->steps = 10000;
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
		if (!strncmp((*argv)[i], "-x0", 4)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-x0' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->x0 = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-r", 3)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-r' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->r = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-steps", 7)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-steps' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->steps = atoi(argv_str);
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
		if (sscanf(line_str, "x0 = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-x0' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->x0 = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "r = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-r' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->r = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "steps = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-steps' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->steps = atoi(argv_str);
			continue;
		}
		fprintf(stderr, "### warning, line can not be parsed: '%s'\n", line_str);
	}
	fclose(fp);
}

void dumpCL(FILE *fp, char prefix[], Params *params) {
	fprintf(fp, "%sx0 = %.16lf\n", prefix, params->x0);
	fprintf(fp, "%sr = %.16lf\n", prefix, params->r);
	fprintf(fp, "%ssteps = %d\n", prefix, params->steps);
}

void finalizeCL(Params *params) {
}

void printHelpCL(FILE *fp) {
	fprintf(fp, "  -x0 <DP float>\n  -r <DP float>\n  -steps <integer>\n  -?: print this message");
}