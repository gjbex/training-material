#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char c = '0';
    long iter_nr, nr_iters = 10;
    unsigned int sleeptime = 1;
    if (argc > 1)       
        nr_iters = atol(argv[2]);
    if (argc > 2)
        sleeptime = (unsigned int) atoi(argv[3]);
    for (iter_nr = 0; iter_nr < nr_iters; iter_nr++) {
        putchar(c++);
        if (c > '9')
            c = '0';
        if (iter_nr % 100 == 0)
            sleep(sleeptime);
    }
    return EXIT_SUCCESS;
}
