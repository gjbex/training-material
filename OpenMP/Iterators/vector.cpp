#include <iostream>
#include <vector>

#ifdef _OPENMP
#include <omp.h>
#endif

double logistic_map(double x0, int nr_steps);

int main(int argc, char *argv[]) {
    const int nr_steps {10000};
    int data_size {20};
    double total {0.0};
    int idx {0};
    if (argc > 1)
        data_size = std::stoi(argv[1]);
    std::vector<int> data(data_size);
#pragma omp parallel shared(data, std::cerr, total, idx) default(none)
    {
        auto thread_num {0};
#ifdef _OPENMP
        thread_num = omp_get_thread_num();
#endif
#ifdef ITERATOR
#pragma omp master
        std::cerr << "using iterator" << std::endl;
#pragma omp for schedule(runtime) reduction(+:total) linear(idx:1)
        for (std::vector<int>::iterator iter = data.begin();
                iter < data.end(); ++iter) {
            *iter = thread_num;
            total += logistic_map(1.0/(++idx), nr_steps);
        }
#else
#pragma omp master
        std::cerr << "using indexing" << std::endl;
#pragma omp for schedule(runtime) reduction(+:total) linear(idx:1)
        for (unsigned long i = 0; i < data.size(); ++i) {
            data[i] = thread_num;
            total += logistic_map(1.0/(++idx), nr_steps);
        }
#endif
    }
    for (const auto& value: data)
        std::cout << value << " ";
    std::cout << std::endl;
    std::cout << total << std::endl;
    return 0;
}

double logistic_map(double x0, int nr_steps) {
    for (int step = 0; step < nr_steps; ++step)
        x0 = x0*3.1*(1.0 - x0);
    return x0;
}
