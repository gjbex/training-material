#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Hello " << (argc > 1 ? argv[1] : "world") << "!" << std::endl;
    return 0;
}
