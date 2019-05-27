#include <iostream>
#include <memory>
#include <random>
#include "tree.h"
#include "tree_init.h"

int main(int argc, char* argv[]) {
    double child_prob {0.3};
    Seed_t seed {1234};
    std::size_t max_depth {20};
    if (argc > 1)
        child_prob = std::stod(argv[1]);
    if (argc > 2)
        seed = std::stoul(argv[2]);
    std::unique_ptr<Node_t> tree = gen_random_tree(child_prob, max_depth, seed);
    print_tree<double>(std::cout, tree.get());
    return 0;
}
