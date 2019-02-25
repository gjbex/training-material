#include <iostream>
#include <unistd.h>

#include "diffusion_system.h"

void print_help(std::ostream& out);

int main(int argc, char *argv[]) {
    const double def_max_time = {1000.0};
    const size_t def_nr_particles {5};
    const size_t def_grid_size {10};
    double max_time {def_max_time};
    size_t nr_particles {def_nr_particles};
    size_t grid_size {def_grid_size};
    bool is_verbose = false;
    char opt {'\0'};
    while ((opt = getopt(argc, argv, "t:p:g:vh")) != -1) {
        try {
            switch (opt) {
                case 't':
                    max_time = stod(optarg);
                    break;
                case 'p':
                    nr_particles = stoi(optarg);
                    break;
                case 'g':
                    grid_size = stoi(optarg);
                    break;
                case 'h':
                    print_help(std::cout);
                    return 0;
                case 'v':
                    is_verbose = true;
                    break;
                default:
                    print_help(std::cerr);
                    return 1;
            }
        } catch (invalid_argument& e) {
            std::cerr << "# error: invalid argument for option -"
                      << opt << endl;
            print_help(std::cerr);
            return 1;
        }
    }
    double time {0.0};
    System system(nr_particles, grid_size);
    system.print_grid();
    while (time < max_time) {
        if (is_verbose)
            cout << "time = " << time << endl;
        if (is_verbose)
            system.print_queue();
        time += system.update();
    }
    system.print_grid();
    return 0;
}

void print_help(std::ostream& out) {
    out << "Usage: diffusion.exe "
        << "[-t <time>] "
        << "[-p <nr_part] "
        << "[-g <grid_size>] "
        << "[-v] "
        << "[-h]" << std::endl;
    out << "\t-t <time>   : time to run x simulation" << std::endl
        << "\t-p <nr_part>: number of particles in simulation" << std::endl
        << "\t-g <size>   : grid size" << std::endl
        << "\t-v          : verbose output" << std::endl
        << "\t-h          : display help message" << std::endl;
}
