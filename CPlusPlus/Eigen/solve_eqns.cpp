#include <Eigen/Dense>
#include <Eigen/SparseLU>
#include <iostream>

int main() {
    Eigen::MatrixXd A(2, 2);
    A << 3.0, -1.5,
         2.5,   0.5; 
    std::cout << "A =" << std::endl << A << std::endl;
    Eigen::VectorXd b(2);
    b << 3.5, -2.5;
    std::cout << "b =" << std::endl << b << std::endl;
    auto decomposition = A.partialPivLu();
    Eigen::VectorXd x = decomposition.solve(b);
    std::cout << "x =" << std::endl << x << std::endl;
    std::cout << "A*x - b =" << std::endl << A*x - b << std::endl;
    return 0;
}

