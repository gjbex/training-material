#include <iostream>

int main() {
    int *a = new int[5];
    int n = 5;
    int m;
    if (m > n) {
        std::cout << "in if-statement" << std::endl;
        for (int i = 0; i <= 5; ++i)
            a[i] = i;
    }
    std::cout << "a[5] = " << a[n] << std::endl;
    return 0;
}
