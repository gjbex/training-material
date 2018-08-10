#include <stdio.h>

int main() {
    enum week_days {monday, tuesday, wednesday, thursday, friday};
    enum week_days day = wednesday;
    printf("day = %d\n", day);
    day  = 13;
    printf("day = %d\n", day);
    return 0;
}
