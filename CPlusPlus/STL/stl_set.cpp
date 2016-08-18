#include <iostream>
#include <set>

int main(int argc, char *argv[]) {
    std::set<int> int_set;
    for (int i = 0; i < 10; i++) {
        int_set.insert(i % 7);
        std::cout << "inserted " << i << ", set size = " << int_set.size()
            << std::endl;
    }
    for (std::set<int>::iterator iter = int_set.begin();
            iter != int_set.end(); iter++)
        std::cout << *iter << std::endl;
    return 0;
}
