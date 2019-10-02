#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("called with %d arguments:\n", argc - 1);
    for (int i = 1; i < argc; i++)
        printf("\t'%s'\n", argv[i]);
    return 0;
}
