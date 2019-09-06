#include <iostream>
#include "double_linked_list.h"

int main() {
    LinkedList<int> list;
    for (int i = 3; i < 12; i += 2)
        list.push_back(i);
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
    return 0;
}
