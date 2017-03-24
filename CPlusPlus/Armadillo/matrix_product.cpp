#include <armadillo>
#include <iostream>

using namespace arma;

int main() {
    mat A(3, 2, fill::randn), B(2, 4, fill::randn);
    std::cout << "A:" << std::endl << A << std::endl;
    std::cout << "B:" << std::endl << B << std::endl;
    mat D = A*B;
    std::cout << "A*B:" << std::endl << D << std::endl;
    return 0;
}
