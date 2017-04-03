#include <iostream>
#include <vector>

void show_vector(std::vector<int> v) {
    for (auto i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int n = 5;
    std::vector<int> v1;
    for (int i = 0; i < n; i++) {
        v1.push_back(2*i);
    }
    show_vector(v1);
    std::vector<int> v2(v1.size());
    for (unsigned i = 0; i < v1.size(); i++) {
        v2[i] = v1[i]*v1[i];
    }
    show_vector(v2);
    return 0;
}
