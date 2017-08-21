#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int v1;
    int v2;
    int v_a1 __attribute__((aligned(64)));
    int v_a2 __attribute__((aligned(64)));
    printf("non-aligned:\n\t%p\n\t%p\n\tdiff: %lu byte\n",
           &v1, &v2, (&v2 - &v1)*sizeof(int));
    printf("aligned:\n\t%p\n\t%p\n\tdiff: %lu byte\n",
           &v_a1, &v_a2, (&v_a2 - &v_a1)*sizeof(int));
    return EXIT_SUCCESS;
}
