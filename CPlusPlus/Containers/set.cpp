#include <iostream>
#include <set>
#include <unordered_set>

int main(int argc, char *argv[]) {
    std::unordered_set<int> u_int_set;
    for (int i = 0; i < 10; i++) {
        u_int_set.insert(i % 7);
    }
    std::cout << "unordered set:" << std::endl;
    for (auto value: u_int_set) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    for (auto i: {1, 3, 5, 7, 9}) {
        auto it = u_int_set.find(i);
        if (it != u_int_set.end()) {
            std::cout << "set contains " << i << std::endl;
        } else {
            std::cout << "set does not contain " << i << std::endl;
        }
    }
    return 0;
}
