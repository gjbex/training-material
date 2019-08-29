#include <chrono>
#include <iostream>
#include <memory>

#include "equations.h"
#include "solver.h"

using my_time_t = std::chrono::nanoseconds;

int main(int argc, char* argv[]) {
    std::unique_ptr<Equations> eqns;
    auto start_time = std::chrono::steady_clock::now();
    if (argc > 1) {
        Seed_t seed {1234};
        if (argc > 2)
            seed = std::stoul(argv[2]);
        eqns = std::make_unique<Equations>(std::stoul(argv[1]), seed);
    } else {
        eqns = std::make_unique<Equations>(std::cin);
    }
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "initialization = " << duration.count()*1.0e-9 << " s" << std::endl;
    start_time = std::chrono::steady_clock::now();
    std::vector<double> x = solve_serial(*eqns);
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "solving = " << duration.count()*1.0e-9 << " s" << std::endl;
    start_time = std::chrono::steady_clock::now();
    std::vector<double> delta = check_serial(*eqns, x);
    double sum {0.0};
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "checking = " << duration.count()*1.0e-9 << " s" << std::endl;
    for (size_t i = 0; i < x.size(); ++i) {
        std::cout << x[i] << " " << delta[i] << "\n";
        sum += delta[i];
    }
    std::cerr << "avg. error = " << sum/delta.size() << std::endl;
    return 0;
}
