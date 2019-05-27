#ifndef TREE_HDR
#define TREE_HDR

#include <iostream>
#include <memory>

template<typename T>
class Node {
    private:
        T data_;
        std::unique_ptr<Node<T>> left_child_;
        std::unique_ptr<Node<T>> right_child_;
    public:
        Node(T data) : data_ {data}, left_child_ {nullptr}, right_child_ {nullptr} {};
        T& operator()() { return data_; }
        Node<T>* left() { return left_child_.get(); }
        Node<T>* right() { return right_child_.get(); }
        void set_left(std::unique_ptr<Node<T>> child) {
            left_child_ = std::move(child);
        }
        void set_right(std::unique_ptr<Node<T>> child) {
            right_child_ = std::move(child);
        }
        friend std::ostream& operator<<(std::ostream& out, const Node<T>& node) {
            out << node.data_;
            return out;
        }
};

template<typename T>
void print_tree(std::ostream& out, Node<T>* node, const std::size_t level = 0) {
    if (node) {
        if (level > 0)
            out << "\n";
        for (std::size_t i = 0; i < level; ++i)
            out << "  ";
        out << level << ": " << (*node);
        print_tree(out, node->left(), level + 1);
        print_tree(out, node->right(), level + 1);
    }
}

#endif
