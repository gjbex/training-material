#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printf(const char *format, ...) {
    va_list arg;
    int done;
    va_start(arg, format);
    done = vprintf(format, arg);
    va_end(arg);
    return done;
}

FILE *fopen(const char *path, const char *mode) {
    char *path_copy;
    size_t str_len = strlen(path) + 1;
    if (!(path_copy = (char *) malloc(str_len*sizeof(char))))
        errx(EXIT_FAILURE, "can not allocate path name copy");
    strncpy(path_copy, path, str_len);
    printf("opening '%s' as '%s'\n", path, mode);
    return (FILE *) path_copy;
}

int fprintf(FILE *stream, const char *format, ...) {
    va_list arg;
    int done;
    printf("printing to '%s':\n", (char *) stream);
    va_start(arg, format);
    done = vprintf(format, arg);
    va_end(arg);
    return done;
}

int __fprintf_chk(FILE *stream, int flag, const char *format, ...) {
    va_list arg;
    int done;
    printf("printing to '%s':\n", (char *) stream);
    va_start(arg, format);
    done = vprintf(format, arg);
    va_end(arg);
    return done;
}

int fclose(FILE *stream) {
    printf("closing '%s'\n", (char *) stream);
    free(stream);
    return EXIT_SUCCESS;
}
