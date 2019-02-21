#include <iostream>
#include <vector>

struct S {
    S() { puts("S()"); }
    S(S&) { puts("S(&)"); }
    S(S&&) { puts("S(&&)"); }
    ~S() { puts("~S()"); }
};

int main() {
    std::vector<S> v;
    for (int i = 0; i < 5; i++)
        v.emplace_back();
    return 0;
}
