#include <armadillo>
#include <iostream>

using namespace arma;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "# error: no file specified" << std::endl;
        return 1;
    }
    mat A;
    A.load(argv[1], raw_ascii);
    std::cout << "matrix:" << std::endl << A << std::endl;
    std::cout << "det(A) = " << det(A) << std::endl;
    return 0;
}
