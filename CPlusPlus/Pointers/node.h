#ifndef NODE_HDR
#define NODE_HDR

#include <ostream>

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
        void to_str(std::ostream& out, const std::string& indent) const {
            out << indent << id() << ": " << _value << std::endl;
            if (has_left())
                left()->to_str(out, indent + "  ");
            if (has_right())
                right()->to_str(out, indent + "  ");
        };
        friend std::ostream& operator<<(std::ostream& out, const Node<T>& node) {
            out << node.id();
            if (node.has_left())
                out << std::endl << (*node.left());
            if (node.has_right())
                out << std::endl << (*node.right());
            return out;
        };
        ~Node<T>() {
            if (has_left())
                delete _left;
            if (has_right())
                delete _right;
        };
};

#endif
