#ifndef TREE_INIT_HDR
#define TREE_INIT_HDR

#include <random>
#include "tree.h"

using Node_t = Node<double>;
using Seed_t = std::mt19937_64::result_type;

std::unique_ptr<Node_t> gen_random_tree(const double child_prob,
                                        const std::size_t max_depth,
                                        const Seed_t seed);

#endif
