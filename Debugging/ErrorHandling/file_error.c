#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define ARG_ERR 1
#define FILE_OPEN_ERR 2

int main(int argc, char *argv[]) {
    if (argc == 1)
        errx(ARG_ERR, "no file name specified");
    FILE *fp;
    char *line = NULL;
    size_t buffer_length = 0;
    ssize_t nr_chars;
    if (!(fp = fopen(argv[1], "r")))
        err(FILE_OPEN_ERR, "can't open file '%s' for reading", argv[1]);
    while ((nr_chars = getline(&line, &buffer_length, fp)) != -1) {
        printf("%3zu: %s", nr_chars, line);
    }
    free(line);
    fclose(fp);
    return 0;
}
