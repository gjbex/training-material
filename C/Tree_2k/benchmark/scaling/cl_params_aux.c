#include <err.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#ifndef CL_ISSTRICT
#define CL_ISSTRICT 1
#endif

#include "cl_params_aux.h"

int isIntCL(char *input, int isVerbose) {
    if (isLongCL(input, isVerbose)) {
        char *end;
        long number = strtol(input, &end, 0);
        return INT_MIN <= number && number <= INT_MAX;
    } else {
        return FALSE;
    }
}

int isLongCL(char *input, int isVerbose) {
    char *end;
    long number;
    errno = 0;
    number = strtol(input, &end, 0);
    if ((errno == ERANGE &&
            (number == LONG_MAX || number == LONG_MIN)) ||
        (errno != 0 && number == 0)) {
        if (isVerbose) {
            char msg[1024];
            sprintf(msg, "### Error for int '%s'", input);
            perror(msg);
        }
        return FALSE;
    } else if (end == input) {
        if (isVerbose) {
            fprintf(stderr, "### Error for int '%s': NaN\n", input);
        }
        return FALSE;
    } else if (*end != '\0') {
        if (CL_ISSTRICT) {
            if (isVerbose) {
                fprintf(stderr, "### Error for int '%s': NaN, trailing '%s'\n", input, end);
            }
            return FALSE;
        } else {
            if (isVerbose) {
                fprintf(stderr, "### Warming for int '%s': trailing '%s'\n", input, end);
            }
            return TRUE;
        }
    } else {
        return TRUE;
    }
}

int isFloatCL(char *input, int isVerbose) {
    if (isDoubleCL(input, isVerbose)) {
        char *end;
        double number = strtod(input, &end);
        return -FLT_MAX <= number && number <= FLT_MAX;
    } else {
        return FALSE;
    }
}

int isDoubleCL(char *input, int isVerbose) {
    char *end;
    long number;
    errno = 0;
    number = strtod(input, &end);
    if ((errno == ERANGE) || (errno != 0 && number == 0)) {
        if (isVerbose) {
            char msg[1024];
            sprintf(msg, "### Error for double '%s'", input);
            perror(msg);
        }
        return FALSE;
    } else if (end == input) {
        if (isVerbose) {
            fprintf(stderr, "### Error for double '%s': NaN\n", input);
        }
        return FALSE;
    } else if (*end != '\0') {
        if (CL_ISSTRICT) {
            if (isVerbose) {
                fprintf(stderr, "### Error for double '%s': NaN, trailing '%s'\n", input, end);
            }
            return FALSE;
        } else {
            if (isVerbose) {
                fprintf(stderr, "### Warming for double '%s': trailing '%s'\n", input, end);
            }
            return TRUE;
        }
    } else {
        return TRUE;
    }
}

void shiftCL(int *i, int argc, char *argv[]) {
    if (*i + 1 < argc) {
        (*i)++;
    } else {
        fprintf(stderr, "### error: option '%s' expects a value\n", argv[*i]);
        exit(EXIT_CL_MISSING_VALUE);
    }
}

int isCommentCL(char *str) {
    while (*str != '\0' && (*str == ' ' || *str == '\t')) {
        str++;
    }
    if (*str == '#') {
        return TRUE;
    } else {
        return FALSE;
    }
}

int isEmptyLineCL(char *str) {
    while (*str != '\0' && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\f')) {
        str++;
    }
    if (*str == '\0') {
        return TRUE;
    } else {
        return FALSE;
    }
}

void stripQuotesCL(char *str) {
    char quote;
    char *pos;
    int i;
    if (str[0] == '\'') {
        quote = '\'';
    } else if (str[0] == '\"') {
        quote = '\"';
    } else {
        fprintf(stderr, "### error, string not properly quoted: %s\n", str);
        exit(EXIT_CL_INVALID_STRING);
    }
    pos = strrchr(str, quote);
    if (pos == str) {
        fprintf(stderr, "### error, string not properly quoted: %s\n", str);
        exit(EXIT_CL_INVALID_STRING);
    }
    if (!isEmptyLineCL(pos + 1)) {
        fprintf(stderr, "### error, trailing characters at end of string: %s\n", str);
        exit(EXIT_CL_INVALID_STRING);
    }
    for (i = 1; (str + i) != pos; i++) {
        str[i - 1] = str[i];
    }
    str[i - 1] = '\0';
}

