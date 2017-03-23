#include <cmath>
#include <iostream>
#include <unistd.h>

class Pendulum {
    private:
        double _freq;
        const double pi {acos(-1.0)};
    public:
        Pendulum() : _freq {1.0} {};
        Pendulum(const double& freq) : _freq {freq} {};
        double operator()(const double& t) {
            return cos(2.0*pi*_freq*t);
        };
        double freq() const { return _freq; };
};

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
    Pendulum pendulum(freq);
    for (double t = 0.0; t <= max_t; t += delta_t)
        std::cout << t << "," << pendulum(t) << std::endl;
    return 0;
}

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
