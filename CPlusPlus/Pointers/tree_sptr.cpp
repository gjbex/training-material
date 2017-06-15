#include <iostream>
#include <memory>
#include "node_sptr.h"

template class Node<double>;

template<typename T>
void build_tree(std::shared_ptr<Node<T>> parent, int depth);

int main(int argc, char *argv[]) {
    auto root {std::make_shared<Node<double>>(0, 1.1)};
    build_tree<double>(root, 3);
    root->to_str(std::cout);
    return 0;
}

template<typename T>
void build_tree(std::shared_ptr<Node<T>> parent, int depth) {
    if (depth == 0)
        return;
    int id = parent->id();
    T value = parent->value();
    auto left_child {std::make_unique<Node<T>>(id + 1, value + 1)};
    parent->set_left(left_child);
    auto right_child {std::make_unique<Node<T>>(id + 2, value + 2)};
    parent->set_right(right_child);
    build_tree(parent->left(), depth - 1);
    build_tree(parent->right(), depth - 1);
}
