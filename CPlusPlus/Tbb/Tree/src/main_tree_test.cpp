#include <iostream>
#include <memory>
#include <random>
#include "tree.h"

using Node_t = Node<double>;
using Seed_t = std::mt19937_64::result_type;

std::unique_ptr<Node_t> gen_random_tree(const double child_prob,
                                        const std::size_t max_depth,
                                        const Seed_t seed);

void print_tree(std::ostream& out, Node_t* node, const std::size_t level = 0) {
    if (node) {
        if (level > 0)
            out << "\n";
        for (std::size_t i = 0; i < level; ++i)
            out << "  ";
        out << level << ": " << (*node)();
        print_tree(out, node->left(), level + 1);
        print_tree(out, node->right(), level + 1);
    }
}

int main(int argc, char* argv[]) {
    double child_prob {0.3};
    Seed_t seed {1234};
    std::size_t max_depth {20};
    if (argc > 1)
        child_prob = std::stod(argv[1]);
    if (argc > 2)
        seed = std::stoul(argv[2]);
    std::unique_ptr<Node_t> tree = gen_random_tree(child_prob, max_depth, seed);
    print_tree(std::cout, tree.get());
    return 0;
}

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

void add_children(Node_t* node, const std::size_t max_depth, std::size_t depth,
                  ChildrenDistritution& child_distr,
                  ValueDistribution& value_distr) {
    if (depth < max_depth) {
        if (child_distr()) {
            double value = value_distr();
            node->set_left(std::make_unique<Node_t>(value));
            add_children(node->left(), max_depth, depth + 1,
                         child_distr, value_distr);
        }
        if (child_distr()) {
            double value = value_distr();
            node->set_right(std::make_unique<Node_t>(value));
            add_children(node->right(), max_depth, depth + 1,
                         child_distr, value_distr);
        }
    }
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
