#include <algorithm>
#include <functional>
#include <iostream>
#include <list>

bool ge_pred(int a, int b) {
    return a >= b;
}

void show_list(std::list<int> int_list) {
    for (auto it = int_list.begin(); it != int_list.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    std::list<int> int_list;
    for (int i = 0; i <= 20; i += 5) {
        int_list.push_back(i);
    }
    std::cout << "size 1: " << int_list.size() << std::endl;
    show_list(int_list);
    for (int i = 12; i >= 8; i--) {
        using namespace std::placeholders;
        auto pred = std::bind(ge_pred, _1, i);
        auto it = std::find_if(int_list.begin(), int_list.end(), pred);
        if (it != int_list.end()) {
            int_list.insert(it, i);
        } else {
            int_list.push_back(i);
        }
    }
    std::cout << "size 1: " << int_list.size() << std::endl;
    show_list(int_list);
    return 0;
}
