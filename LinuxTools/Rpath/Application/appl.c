#include <stdio.h>
#include <stdlib.h>

#include <hello.h>

int main(int argc, char *argv[]) {
    if (argc > 1)
        say_hello(argv[1]);
    else
        printf("no one to say hello to...\n");
    return EXIT_SUCCESS;
}
