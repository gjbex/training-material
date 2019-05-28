#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <tbb/tbb.h>
#include "tree.h"
#include "sum_task.h"
#include "tree_init.h"

using my_time_t = std::chrono::nanoseconds;

int main(int argc, char* argv[]) {
    double child_prob {0.3};
    Seed_t seed {1234};
    std::size_t max_depth {20};
    if (argc > 1)
        child_prob = std::stod(argv[1]);
    if (argc > 2)
        seed = std::stoul(argv[2]);
    TreeInit tree_init(child_prob, max_depth, seed);
    std::unique_ptr<Node_t> tree = tree_init.gen_random_tree();
    print_tree<double>(std::cout, tree.get());
    std::cout << std::endl;
    double sum {0.0};
    auto start_time = std::chrono::steady_clock::now();
    auto task = new(tbb::task::allocate_root()) SumTask<double>(tree.get(), &sum);
    tbb::task::spawn_root_and_wait(*task);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "time: " << duration.count()*1.0e-9 << " s" << std::endl;
    std::cout << "sum = " << sum << std::endl;
    return 0;
}
