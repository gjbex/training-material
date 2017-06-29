#include <iostream>
#include "node.h"

template class Node<double>;

template<typename T>
void build_tree(Node<T>* parent, int depth);

int main(int argc, char *argv[]) {
    auto root {new Node<double>(0, 1.1)};
    build_tree<double>(root, 3);
    root->to_str(std::cout);
    delete root;
    return 0;
}

template<typename T>
void build_tree(Node<T>* parent, int depth) {
    if (depth == 0)
        return;
    int id = parent->id();
    T value = parent->value();
    auto left_child {new Node<T>(id + 1, value + 1)};
    parent->set_left(left_child);
    auto right_child {new Node<T>(id + 2, value + 2)};
    parent->set_right(right_child);
    build_tree(left_child, depth - 1);
    build_tree(right_child, depth - 1);
}
