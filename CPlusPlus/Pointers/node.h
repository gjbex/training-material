#ifndef NODE_HDR
#define NODE_HDR

#include <iostream>
#include <memory>

template<typename T>
class Node {
    private:
        int _id;
        T _value;
        Node<T>* _left;
        Node<T>* _right;
    public:
        Node(int id, T value) :
            _id {id}, _value {value}, _left {nullptr}, _right {nullptr} {};
        int id() const { return _id; };
        T value() const { return _value; };
        void set_value(T v) { _value = v; };
        bool has_left() const { return _left != nullptr; };
        Node<T>* left() const { return _left; };
        void set_left(Node<T>* child) { _left = child; };
        bool has_right() const { return _right != nullptr; };
        Node<T>* right() const { return _right; };
        void set_right(Node<T>* child) { _right = child; };
        void to_str(std::ostream& out) const { to_str(out, ""); };
        void to_str(std::ostream& out, const std::string& indent) const;
        ~Node<T>() {
            if (has_left())
                delete _left;
            if (has_right())
                delete _right;
        };
};

#include "node.cpp"

#endif
