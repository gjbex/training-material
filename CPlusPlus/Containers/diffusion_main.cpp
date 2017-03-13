#include <iostream>

#include "diffusion_system.h"

int main() {
    const double max_time = {10.0};
    double time {0.0};
    const size_t nr_particles {5};
    const size_t grid_size {10};
    System system(nr_particles, grid_size);
    while (time < max_time) {
        cout << "time = " << time << endl;
        system.print_queue();
        time += system.update();
        cout << "new time = " << time << endl;
    }
    system.print_grid();
    return 0;
}
