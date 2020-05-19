#include <iostream>

int fac(int n) {
    if (n == 0)
        return 1;
    else
        return n*fac(n - 1);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: expecting integer argument\n";
        return 1;
    }
    int n {std::stoi(argv[1])};
    if (n < 0) {
        std::cerr << "Error: argument must be positive\n";
        return 2;
    }
    std::cout << fac(n) << "\n";
    return 0;
}
