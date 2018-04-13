#ifndef MEMDUMP
#define MEMDUMP

#include <stdio.h>

#define DUMP(x) \
    { \
        fprintf(stderr, "stack "); \
        fprintf(stderr, #x); \
        fprintf(stderr, "\t%p\t%lu\n", &(x), sizeof(x)); \
    }

#define DUMP_PTR(x) \
    { \
        fprintf(stderr, "heap  "); \
        fprintf(stderr, #x); \
        fprintf(stderr, "\t%p\t%lu\n", (x), sizeof(*(x))); \
    }

#define DUMP_ARRAY(x, n) \
    { \
        int i; \
        for (int i = 0; i < n; i++) { \
            fprintf(stderr, "stack "); \
            fprintf(stderr, #x); \
            fprintf(stderr, "[%d]\t%p\t%lu\n", i, &(x[i]), sizeof(x[i])); \
        } \
    }

#define DUMP_PTR_ARRAY(x, n) \
    { \
        int i; \
        for (int i = 0; i < n; i++) { \
            fprintf(stderr, "heap  "); \
            fprintf(stderr, #x); \
            fprintf(stderr, "[%d]\t%p\t%lu\n", i, &(x[i]), sizeof(x[i])); \
        } \
    }

#endif
