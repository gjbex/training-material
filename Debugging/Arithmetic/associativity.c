#include <float.h>
#include <stdio.h>

int main() {
    const float delta = FLT_EPSILON/2.0f;
    printf("%d\n", 1.0f + (delta + delta + delta) == ((1.0f + delta) + delta) + delta);
    printf("%d\n", 1.35f + (3.17f + 2.9f) == (1.35f + 3.17f) + 2.9f);
    return 0;
}
