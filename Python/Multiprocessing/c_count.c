#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char c;
    long nr_A = 0, nr_C = 0, nr_G = 0, nr_T = 0;
    while (c = getchar()) {
        switch (c) {
            case 'A':
                nr_A++;
                break;
            case 'C':
                nr_C++;
                break;
            case 'G':
                nr_G++;
                break;
            case 'T':
                nr_T++;
                break;
        }
        if (feof(stdin)) break;
    }
    printf("A: %ld\nC: %ld\nG: %ld\nT: %ld\ntotal: %ld\n",
            nr_A, nr_C, nr_G, nr_T, nr_A + nr_C + nr_G + nr_T);
    return EXIT_SUCCESS;
}
