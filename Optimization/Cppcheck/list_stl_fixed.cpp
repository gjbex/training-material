#include <list>
#include <iostream>

int main(int argc, char *argv[]) {
    std::list<int> int_list1;
    std::list<int> *int_list2 = new std::list<int>();
    for (int i = 0; i < 10; i++) {
        int_list1.push_back(i);
        int_list2->push_back(i);
    }
    std::cout << "size 1: " << int_list1.size() << std::endl;
    std::cout << "size 2: " << int_list2->size() << std::endl;
    for (std::list<int>::iterator iter = int_list1.begin();
            iter != int_list1.end(); ++iter) {
        std::cout << "1: " << *iter << std::endl;
    }
    for (std::list<int>::iterator iter = int_list2->begin();
            iter != int_list2->end(); ++iter) {
        std::cout << "2: " << *iter << std::endl;
    }
    delete int_list2;
}
