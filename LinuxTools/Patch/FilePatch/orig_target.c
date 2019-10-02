#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("----\n");
    printf("%s called with %d arguments:\n", argv[0], argc - 1);
    for (int i = 1; i < argc; i++)
        printf("\t'%s'\n", argv[i]);
    printf("----\n");
    return 0;
}

