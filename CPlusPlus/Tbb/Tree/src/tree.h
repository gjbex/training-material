#ifndef TREE_HDR
#define TREE_HDR

#include <iostream>
#include <memory>

class TreeInit;

template<typename T>
class Node {
    private:
        T data_;
        std::unique_ptr<Node<T>> left_child_;
        std::unique_ptr<Node<T>> right_child_;
        Node<T>* parent_;
        std::size_t nr_descendants_;
        void set_parent(Node<T>* parent) { parent_ = parent; }
    public:
        Node(T data) : data_ {data}, left_child_ {nullptr}, right_child_ {nullptr},
           parent_ {nullptr} {}
        std::size_t nr_descendants() const { return nr_descendants_; }
        T& operator()() { return data_; }
        Node<T>* left() { return left_child_.get(); }
        Node<T>* right() { return right_child_.get(); }
        void set_left(std::unique_ptr<Node<T>> child) {
            left_child_ = std::move(child);
            left_child_->set_parent(this);
        }
        void set_right(std::unique_ptr<Node<T>> child) {
            right_child_ = std::move(child);
            right_child_->set_parent(this);
        }
        friend std::ostream& operator<<(std::ostream& out, const Node<T>& node) {
            out << node.data_;
            return out;
        }
        friend TreeInit;
};

template<typename T>
void print_tree(std::ostream& out, Node<T>* node, const std::size_t level = 0) {
    if (node) {
        if (level > 0)
            out << "\n";
        for (std::size_t i = 0; i < level; ++i)
            out << "  ";
        out << level << " (" << node->nr_descendants() << "): " << (*node);
        print_tree(out, node->left(), level + 1);
        print_tree(out, node->right(), level + 1);
    }
}

#endif
