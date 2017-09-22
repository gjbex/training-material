#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *string = NULL;
    if (argc > 1) {
        const size_t len = strlen(argv[1]) + 1;
        string = (char *) malloc(sizeof(char)*len);
        if (string == NULL)
            errx(EXIT_FAILURE, "can't allocate string\n");
        strncpy(string, argv[1], len);
    }
    if (strlen(string) > 0 && string != NULL)
        printf("hello %s!\n", string);
    return EXIT_SUCCESS;
}
