#include <iostream>
#include <unistd.h>

#include "pendulum_utils.h"

void print_help() {
    std::cerr << "Usage: pendulum.exe "
              << "[ -f <freq> ] "
              << "[ -d <delta_t> ] "
              << "[ -m <max_t> ] "
              << std::endl;
    std::cerr << "\t-f <freq>    : pendulum frequency" << std::endl;
    std::cerr << "\t-d <delta_t> : time increment" << std::endl;
    std::cerr << "\t-m <max_t>   : maximum time for the pendulum"
              << std::endl;
}

Parameters get_parameters(int argc, char *argv[]) {
    double freq {1.0};
    double delta_t {0.005};
    double max_t {1.0};
    char opt {'\0'};
    while ((opt = getopt(argc, argv, "f:d:m:h")) != -1) {
        switch (opt) {
            case 'f':
                freq = std::stod(optarg);
                break;
            case 'd':
                delta_t = std::stod(optarg);
                break;
            case 'm':
                max_t = std::stod(optarg);
                break;
            case 'h':
                print_help();
                exit(0);
            default:
                std::cerr << "# error: unknown option" << std::endl;
                print_help();
                exit(1);
        }
    }
    return std::make_tuple(freq, delta_t, max_t);
}

void integrate(std::function<double(double)> f,
               const double& delta_t, const double& max_t) {
    for (double t = 0.0; t <= max_t + 0.1*delta_t; t += delta_t)
        std::cout << t << "," << f(t) << std::endl;
}
