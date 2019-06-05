#define EIGEN_USE_MKL_ALL
#include <chrono>
#include <Eigen/Dense>
#include <iostream>

using Time_t = std::chrono::nanoseconds;
using namespace std::chrono_literals;

int main(int argc, char* argv[]) {
    int nr_prods {1};
    if (argc > 1)
        nr_prods = std::stoi(argv[1]);
    std::chrono::duration<double> duration = 0ns;
    for (int prod_nr = 0; prod_nr < nr_prods; ++prod_nr) {
        Eigen::MatrixXd A = Eigen::MatrixXd::Random(10000, 2000);
        Eigen::MatrixXd B = Eigen::MatrixXd::Random(2000, 8000);
        auto stime {std::chrono::steady_clock::now()};
        Eigen::MatrixXd C = A*B;
        auto etime {std::chrono::steady_clock::now()};
        duration += std::chrono::duration_cast<Time_t>(etime - stime);
        std::cout << "C.sum() = " << C.sum() << std::endl;
    }
    std::cout << "time: " << duration.count()/nr_prods
              << " s" << std::endl;
    return 0;
}
