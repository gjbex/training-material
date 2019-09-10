#include <iostream>
#include "double_linked_list.h"

int main() {
    LinkedList<int> list;
    for (int i = 3; i < 12; i += 2)
        list.push_back(i);
    list.push_back(13);
    std::cout << "list:";
    for (const auto& value: list)
        std::cout << " " << value;
    std::cout << std::endl;
    std::cout << "list:";
    for (const auto& value: list)
        std::cout << " " << value;
    std::cout << std::endl;
    while (!list.is_empty()) {
        auto value = list.back();
        list.pop_back();
        std::cout << "popped " << value << ", list: ";
        for (const auto& value: list)
            std::cout << " " << value;
        std::cout << std::endl;
    }
    for (int i = 3; i < 12; i += 2)
        list.push_front(i);
    std::cout << "list:";
    for (const auto& value: list)
        std::cout << " " << value;
    std::cout << std::endl;
    while (!list.is_empty()) {
        auto value = list.front();
        list.pop_front();
        std::cout << "popped " << value << ", list: ";
        for (const auto& value: list)
            std::cout << " " << value;
        std::cout << std::endl;
    }
    for (int i = 3; i < 12; i += 2)
        list.push_back(i);
    auto it = std::begin(list);
    for (size_t i = 0; i < 2; ++i) {
        std::cout << "now at " << *it << "\n";
        ++it;
    }
    auto new_it = list.insert(it, 8);
    std::cout << "inserted " << *new_it << " after " << *it << std::endl;
    std::cout << "list:";
    for (const auto& value: list)
        std::cout << " " << value;
    std::cout << std::endl;
    LinkedList<int*> p_list;
    for (int i = 3; i < 12; i += 2)
        p_list.push_front(new int(i));
    std::cout << "pointer list:";
    for (const auto& value: p_list)
        std::cout << " " << *value;
    std::cout << std::endl;
    for (const auto& value: p_list)
        delete value;
    return 0;
}
