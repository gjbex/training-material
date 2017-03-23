#include <cmath>
#include <functional>
#include <iostream>
#include <unistd.h>

const double pi {acos(-1.0)};

double pendulum_func(double t, double freq) {
    return cos(2.0*pi*freq*t);
}

void print_help();

int main(int argc, char *argv[]) {
    double freq {1.0};
    double max_t {1.0};
    double delta_t {0.005};
    char opt {'\0'};
    while ((opt = getopt(argc, argv, "f:d:m:h")) != -1) {
        switch (opt) {
            case 'f':
                freq = std::stof(optarg);
                break;
            case 'd':
                delta_t = std::stof(optarg);
                break;
            case 'm':
                max_t = std::stof(optarg);
                break;
            case 'h':
                print_help();
                return 0;
            default:
                std::cerr << "# error: unknown option" << std::endl;
                print_help();
                return 1;
        }
    }
    using namespace std::placeholders;
    auto pendulum = std::bind(pendulum_func, _1, freq);
    for (double t = 0.0; t <= max_t; t += delta_t)
        std::cout << t << "," << pendulum(t) << std::endl;
    return 0;
}

void print_help() {
    std::cerr << "Usage: pendulum_bind.exe "
              << "[ -f <freq> ] "
              << "[ -d <delta_t> ] "
              << "[ -m <max_t> ] "
              << std::endl;
    std::cerr << "\t-f <freq>    : pendulum frequency" << std::endl;
    std::cerr << "\t-d <delta_t> : time increment" << std::endl;
    std::cerr << "\t-m <max_t>   : maximum time for the pendulum"
              << std::endl;
}
