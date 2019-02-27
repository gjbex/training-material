#include <iostream>
#include <array>
#include <list>
#include <valarray>

// use T_coll&& to make it work for rvalues
template<typename T_coll>
void print_collection(const std::string& label, T_coll&& coll) {
    std::cout << label << ":";
    for (const auto& value: coll)
        std::cout << " " << value;
    std::cout << std::endl;
};

using Vector = std::valarray<double>;

// Note that the return type of operator+(const valarray&, const valarray&)
// is *not* valarray!
Vector sum(const Vector v1, Vector v2) {
    return v1 + v2;
}

int main() {
    std::array<int, 3> a {-1, 0, 1};
    std::list<std::string> l {"abc", "def", "ghi"};
    print_collection("array", a);
    print_collection("list", l);
    // does it work for an rvalue?
    Vector v1 {1.0, 2.0, 3.0};
    Vector v2 {-1.0, 3.0, -2.0};
    print_collection("v1 + v2", sum(v1, v2));
    return 0;
}
