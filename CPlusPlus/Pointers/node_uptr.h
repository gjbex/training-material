#ifndef NODE_HDR
#define NODE_HDR

#include <ostream>
#include <memory>

template<typename T>
class Node {
    private:
        int _id;
        T _value;
        std::unique_ptr<Node<T>> _left;
        std::unique_ptr<Node<T>> _right;
    public:
        Node(int id, T value) :
            _id {id}, _value {value}, _left {nullptr}, _right {nullptr} {};
        Node(Node<T>&& other) : _id {other._id}, _value {other._value} {
            _left = std::move(other._left);
            _right = std::move(other._right);
        };
        int id() const { return _id; };
        T value() const { return _value; };
        void set_value(T v) { _value = v; };
        bool has_left() const { return _left != nullptr; };
        Node<T>& left() {
            return *_left.get();
        };
        void set_left(std::unique_ptr<Node<T>>& child) {
            _left = std::move(child);
        };
        bool has_right() const { return _right != nullptr; };
        Node<T>& right() {
            return *_right.get();
        };
        void set_right(std::unique_ptr<Node<T>>& child) {
            _right = std::move(child);
        };
        void to_str(std::ostream& out) { to_str(out, ""); };
        void to_str(std::ostream& out, const std::string& indent) {
            out << indent << id() << ": " << _value << std::endl;
            if (has_left())
                left().to_str(out, indent + "  ");
            if (has_right())
                right().to_str(out, indent + "  ");
        };
};

#endif
