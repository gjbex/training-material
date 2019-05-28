#ifndef TREE_INIT_HDR
#define TREE_INIT_HDR

#include <functional>
#include <random>
#include "tree.h"

using Node_t = Node<double>;
using Seed_t = std::mt19937_64::result_type;

class TreeInit {
    private:
        const std::size_t max_depth_;
        const double child_prob_;
        std::unique_ptr<std::mt19937_64> engine_;
        std::function<double()> value_distr_;
        std::function<double()> unif_distr_;
        std::function<bool()> child_distr_;
    public:
        TreeInit(const double child_prob, const std::size_t max_depth,
                 const Seed_t seed);
        std::unique_ptr<Node_t> gen_random_tree();
        std::size_t add_children(Node_t* node, const std::size_t depth);
};

#endif
