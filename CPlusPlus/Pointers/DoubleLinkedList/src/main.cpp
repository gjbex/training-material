#include <functional>
#include <iostream>
#include <string>
#include "double_linked_list.h"

template<typename T>
void print_list(const std::string& label, const LinkedList<T>& list) {
    std::cout << label << ":";
    for (const auto& value: list)
        std::cout << " " << value;
    std::cout << std::endl;
}

template<typename T>
void print_list(const std::string& label, const LinkedList<T>& list,
                std::function<std::string(T)> format) {
    std::cout << label << ":";
    for (const auto& value: list)
        std::cout << " " << format(value);
    std::cout << std::endl;
}

int main() {
    LinkedList<int> list;
    for (int i = 3; i < 12; i += 2)
        list.push_back(i);
    list.push_back(13);
    print_list<int>("list", list);
    while (!list.is_empty()) {
        auto value = list.back();
        list.pop_back();
        print_list("pop back " + std::to_string(value), list);
    }
    for (int i = 3; i < 12; i += 2)
        list.push_front(i);
    print_list<int>("list", list);
    while (!list.is_empty()) {
        auto value = list.front();
        list.pop_front();
        print_list("pop front " + std::to_string(value), list);
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
    print_list<int>("list", list);
    LinkedList<int*> p_list;
    for (int i = 3; i < 12; i += 2)
        p_list.push_front(new int(i));
    print_list<int*>("pointer list", p_list,
                     [] (int* x) -> std::string { return std::to_string(*x); });
    for (const auto& value: p_list)
        delete value;
    LinkedList<std::string> str_list;
    std::string s{"string 0"};
    auto str_list_it = str_list.insert(std::begin(str_list), s);
    for (int i = 1; i < 4; ++i) {
        std::string s{"string "};
        s += std::to_string(i);
        str_list_it = str_list.insert(str_list_it, s);
    }
    print_list<std::string>("string list", str_list);
    return 0;
}
