#include "tree_init.h"

TreeInit::TreeInit(const double child_prob, const std::size_t max_depth,
                   const Seed_t seed) : max_depth_ {max_depth},
                                        child_prob_ {child_prob} {
    engine_ = std::make_unique<std::mt19937_64>(seed);
    value_distr_ = std::bind(std::normal_distribution<double>(0.0, 1.0),
            std::ref(*engine_));
    unif_distr_ = std::bind(std::uniform_real_distribution<double>(0.0, 1.0),
            std::ref(*engine_));
    child_distr_ = [&] () {
        return unif_distr_() < child_prob_;
    };
}

std::size_t TreeInit::add_children(Node_t* node, const std::size_t depth) {
    std::size_t nr_descendants {0};
    if (depth < max_depth_) {
        if (child_distr_()) {
            double value = value_distr_();
            node->set_left(std::make_unique<Node_t>(value));
            node->left()->nr_descendants_ = add_children(node->left(), depth + 1);
            nr_descendants += 1 + node->left()->nr_descendants_;
        }
        if (child_distr_()) {
            double value = value_distr_();
            node->set_right(std::make_unique<Node_t>(value));
            node->right()->nr_descendants_ = add_children(node->right(), depth + 2);
            nr_descendants += 1 + node->right()->nr_descendants_;
        }
    }
    return nr_descendants;
}

std::unique_ptr<Node_t> TreeInit::gen_random_tree() {
    auto root = std::make_unique<Node_t>(value_distr_());
    root->nr_descendants_ = add_children(root.get(), 0);
    return root;
}
