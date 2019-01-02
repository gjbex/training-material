#include <chrono>
#include <iostream>

using my_time = std::chrono::nanoseconds;

extern "C" double quad_(double);

inline double quad(double x) {
    return (3.14*x - 2.4)*x + 1.9;
}

int main(int argc, char *argv[]) {
    unsigned long n {1000};
    if (argc == 2)
        n = std::stoul(argv[1]);
    double delta {1.0/n};
    double sum {0.0};
    auto start_time = std::chrono::steady_clock::now();
    for (unsigned long i = 0; i < n; ++i)
        sum += quad(i*delta);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time>(end_time - start_time);
    std::cout << "C++ quad: " << duration.count()*1.0e-9 << " s"
              << std::endl;
    double nsm_sum {0.0};
    start_time = std::chrono::steady_clock::now();
    for (unsigned long i = 0; i < n; ++i)
        nsm_sum += quad_(i*delta);
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time>(end_time - start_time);
    std::cout << "nasm quad: " << duration.count()*1.0e-9 << " s"
              << std::endl;
    std::cout << "difference: " << sum - nsm_sum << std::endl;
    return 0;
}
