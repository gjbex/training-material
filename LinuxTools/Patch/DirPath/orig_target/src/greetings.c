#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcs.h>

int main(int argc, char *argv[]) {
    switch (argc) {
        case 1:
            say_hello("Nobody");
            break;
        case 2:
            say_hello(argv[1]);
            break;
        case 3:
            if (strcmp(argv[1], "-h") == 0)
                say_hello(argv[2]);
            else if (strcmp(argv[1], "-b") == 0)
                say_bye(argv[2]);
            else {
                fprintf(stderr, "unknown option %s\n", argv[1]);
                exit(1);
            }
            break;
        default:
            fprintf(stderr, "too many options\n");
            exit(2);
    }
    return 0;
}
