#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "cl_params.h"
#include "cl_params_aux.h"

#define MAX_CL_OPT_LEN 128
#define MAX_CL_LINE_LEN 1024

void initCL(Params *params) {
	params->N = 500;
	params->nr_iters = 1;
	params->skip_gpu_xt = false;
	params->skip_gpu = false;
	params->skip_cpu = false;
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
		if (!strncmp((*argv)[i], "-N", 3)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-N' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->N = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-nr_iters", 10)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-nr_iters' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->nr_iters = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-skip_gpu_xt", 13)) {
			params->skip_gpu_xt = true;
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-skip_gpu", 10)) {
			params->skip_gpu = true;
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-skip_cpu", 10)) {
			params->skip_cpu = true;
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
		if (sscanf(line_str, "N = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-N' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->N = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "nr_iters = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-nr_iters' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->nr_iters = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "skip_gpu_xt = %[^\n]", argv_str) == 1) {
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-skip_gpu_xt' of type bool\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			if (!strncmp("false", argv_str, 6)) {
				params->skip_gpu_xt = false;
			} else if (!strncmp("true", argv_str, 5)) {
				params->skip_gpu_xt = true;
			} else {
				params->skip_gpu_xt = atoi(argv_str);
			}
			continue;
		}
		if (sscanf(line_str, "skip_gpu = %[^\n]", argv_str) == 1) {
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-skip_gpu' of type bool\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			if (!strncmp("false", argv_str, 6)) {
				params->skip_gpu = false;
			} else if (!strncmp("true", argv_str, 5)) {
				params->skip_gpu = true;
			} else {
				params->skip_gpu = atoi(argv_str);
			}
			continue;
		}
		if (sscanf(line_str, "skip_cpu = %[^\n]", argv_str) == 1) {
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-skip_cpu' of type bool\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			if (!strncmp("false", argv_str, 6)) {
				params->skip_cpu = false;
			} else if (!strncmp("true", argv_str, 5)) {
				params->skip_cpu = true;
			} else {
				params->skip_cpu = atoi(argv_str);
			}
			continue;
		}
		fprintf(stderr, "### warning, line can not be parsed: '%s'\n", line_str);
	}
	fclose(fp);
}

void dumpCL(FILE *fp, char prefix[], Params *params) {
	fprintf(fp, "%sN = %d\n", prefix, params->N);
	fprintf(fp, "%snr_iters = %d\n", prefix, params->nr_iters);
	fprintf(fp, "%sskip_gpu_xt = %d\n", prefix, params->skip_gpu_xt);
	fprintf(fp, "%sskip_gpu = %d\n", prefix, params->skip_gpu);
	fprintf(fp, "%sskip_cpu = %d\n", prefix, params->skip_cpu);
}

void finalizeCL(Params *params) {
}

void printHelpCL(FILE *fp) {
	fprintf(fp, "  -N <integer>\n  -nr_iters <integer>\n  -skip_gpu_xt\n  -skip_gpu\n  -skip_cpu\n  -?: print this message");
}