#include <ostream>
#include "node.h"

template<typename T>
void Node<T>::to_str(std::ostream& out, const std::string& indent) const {
    out << indent << id() << ": " << _value << std::endl;
    if (has_left())
        (*left()).to_str(out, indent + "  ");
    if (has_right())
        (*right()).to_str(out, indent + "  ");
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>& node) {
    out << node.id();
    if (node.has_left())
        out << std::endl << (*node.left());
    if (node.has_right())
        out << std::endl << (*node.right());
    return out;
}
