#include "tree_init.h"

class ValueDistribution {
    private:
        std::mt19937_64& engine_;
        std::normal_distribution<double> distr_;
    public:
        ValueDistribution(std::mt19937_64& engine) :
            engine_ {engine},
            distr_ {std::normal_distribution<double>(0.0, 1.0)} {}
        double operator()() { return distr_(engine_); }
};

class ChildrenDistritution {
    private:
        std::mt19937_64& engine_;
        std::uniform_real_distribution<double> distr_;
        double child_prob_;
    public:
        ChildrenDistritution(std::mt19937_64& engine, const double child_prob) :
            engine_ {engine},
            distr_ {std::uniform_real_distribution<double>(0.0, 1.0)},
            child_prob_ {child_prob} {}
        bool operator()() { return distr_(engine_) < child_prob_; }
};

std::size_t add_children(Node_t* node, const std::size_t max_depth, std::size_t depth,
                         ChildrenDistritution& child_distr,
                         ValueDistribution& value_distr) {
    std::size_t nr_descendants {0};
    if (depth < max_depth) {
        if (child_distr()) {
            double value = value_distr();
            node->set_left(std::make_unique<Node_t>(value));
            nr_descendants += 1 + add_children(node->left(), max_depth, depth + 1,
                                               child_distr, value_distr);
        }
        if (child_distr()) {
            double value = value_distr();
            node->set_right(std::make_unique<Node_t>(value));
            nr_descendants += 1 + add_children(node->right(), max_depth, depth + 1,
                                               child_distr, value_distr);
        }
    }
    return nr_descendants;
}

std::unique_ptr<Node_t> gen_random_tree(const double child_prob,
                                        const std::size_t max_depth,
                                        const Seed_t seed) {
    std::mt19937_64 engine(seed);
    ValueDistribution value_distr(engine);
    auto root = std::make_unique<Node_t>(value_distr());
    ChildrenDistritution child_distr(engine, child_prob);
    add_children(root.get(), max_depth, 1, child_distr, value_distr);
    return root;
}
