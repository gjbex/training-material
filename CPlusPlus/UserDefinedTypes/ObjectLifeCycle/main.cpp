#include <iostream>
#include <vector>

#include "gadget.h"

void greet_by_value(Gadget g) {
    std::cerr << "greet_by_value with " << g.id() << std::endl;
    g.greet();
}

void greet_by_reference(Gadget& g) {
    std::cerr << "greet_by_reference with " << g.id() << std::endl;
    g.greet();
}

Gadget get_gadget(int value) {
    Gadget g(value);
    std::cerr << "Gadget " << g.id() << "(" << value << ")"
              << " in get_gadget" << std::endl;
    return g;
}

std::vector<Gadget> get_lots_of_gadgets(int n) {
    std::vector<Gadget> gadgets;
    for (int i = 0; i < n; ++i)
        gadgets.emplace_back(i);
    std::cerr << "vector fill done" << std::endl;
    return gadgets;
}

int main() {
    std::cerr << "### declations with initialization" << std::endl;
    Gadget g1;
    Gadget g2(5);
    Gadget g3 {g2};
    std::cerr << std::endl;

    std::cerr << "### assignment" << std::endl;
    g1 = g2;
    std::cerr << std::endl;

    std::cerr << "### calling greet_by_value with " << g1.id() << std::endl;
    greet_by_value(g1);
    std::cerr << std::endl;

    std::cerr << "### calling greet_by_reference with " << g1.id()
              << std::endl;
    greet_by_reference(g1);
    std::cerr << std::endl;

    std::cerr << "### return stack variable" << std::endl;
    Gadget g4 = get_gadget(19);
    std::cerr << "Gadget " << g4.id() << " returned by get_gadget"
              << std::endl;
    std::cerr << std::endl;

    std::cerr << "### adding to vector using push_back" << std::endl;
    std::vector<Gadget> gadgets1;
    for (int i = 0; i < 3; i++) {
        Gadget g(i);
        gadgets1.push_back(g);
    }
    std::cerr << std::endl;

    std::cerr << "### adding to vector using emplace_back" << std::endl;
    std::vector<Gadget> gadgets2;
    for (int i = 0; i < 3; i++) {
        gadgets2.emplace_back(i);
    }
    std::cerr << std::endl;
    
    std::cerr << "### calling get_lots_of_gadgets" << std::endl;
    std::vector<Gadget> gadgets3 = get_lots_of_gadgets(3);
    std::cerr << std::endl;

    std::cerr << "### destructors for Gadgets that go out of scope"
              << std::endl;
    return 0;
}
