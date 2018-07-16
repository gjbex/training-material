#include <stdio.h>
#include <stdlib.h>

#ifdef COMPILE_ERROR
void const_int_ptr_fail(const int *n) {
    *n = 27;
}
#endif

void const_int_ptr(const int *n) {
    n = (int *) malloc(sizeof(int));
    printf("in const_int_ptr: %d\n", *n);
}

#ifdef COMPILE_ERROR
void const_int_ptr_fail2(const int *n) {
    n = (int *) malloc(sizeof(int));
    *n = 48;
}
#endif

#ifdef COMPILE_ERROR
void int_ptr_const_fail(int* const n) {
    n = (int *) malloc(sizeof(int));
    printf("in const_int_ptr: %d\n", *n);
}
#endif

void int_ptr_const(int* const n) {
    *n = 23;
}

int main() {
    int n = 5;
    printf("before: %d\n", n);
    int_ptr_const(&n);
    printf("after int_ptr_const: %d\n", n);
    const_int_ptr(&n);
    printf("after const_int_ptr: %d\n", n);
    return 0;
}

