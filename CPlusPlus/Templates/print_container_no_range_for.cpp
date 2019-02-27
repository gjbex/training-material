#include <iostream>
#include <array>
#include <list>
#include <valarray>

// use T_coll&& to make it work for rvalues
template<typename T_coll>
void print_collection(const std::string& label, T_coll&& coll) {
    std::cout << label << ":";
    for (size_t i = 0; i < coll.size(); ++i)
        std::cout << " " << coll[i];
    std::cout << std::endl;
};

using Vector = std::valarray<double>;

int main() {
    std::array<int, 3> a {-1, 0, 1};
    std::list<std::string> l {"abc", "def", "ghi"};
    print_collection("array", a);
    // does it work for an rvalue?
    Vector v1 {1.0, 2.0, 3.0};
    Vector v2 {-1.0, 3.0, -2.0};
    // The crazy stuff return by valarray's + does have a size() member
    // function.
    print_collection("v1 + v2", v1 + v2);
    return 0;
}

