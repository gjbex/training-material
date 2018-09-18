#include <stdio.h>
#include <stdio.h>

int main() {
    unsigned long counter = 0;
    int value = 0;
    for (;;) {
        counter++;
        if (value == 23)
            printf("counter = %lu\n", counter);
        value++;
    }
    return 0;
}
