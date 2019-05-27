#include <iostream>
#include <set>
#include <unordered_set>

int main() {
    std::set<int> int_set;
    std::unordered_set<int> u_int_set;
    for (int i = 0; i < 10; i++) {
        int_set.insert(i % 7);
        u_int_set.insert(i % 7);
        std::cout << "inserted " << i << ", set size = " << int_set.size()
            << std::endl;
    }
    std::cout << "set:" << std::endl;
    for (std::set<int>::iterator iter = int_set.begin();
            iter != int_set.end(); ++iter)
        std::cout << *iter << std::endl;
    std::cout << "unordered set:" << std::endl;
    for (std::unordered_set<int>::iterator iter = u_int_set.begin();
            iter != u_int_set.end(); ++iter)
        std::cout << *iter << std::endl;
    return 0;
}
