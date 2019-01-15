#include <iostream>

int main() {
    int a = 3;
    int b = 5;
    int *ptr = &a;
    std::cout << "*ptr: " << *ptr << std::endl;
    ptr = &b;
    *ptr = 7;
    std::cout << "b: " << b << std::endl;
    int &ref = a;
    std::cout << "ref: " << ref << std::endl;
    ref = b;
    std::cout << "a: " << a << std::endl;
    return 0;
}
