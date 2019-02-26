#include <iostream>
#include <vector>

struct S {
    S() { puts("S()"); }
    S(const S&) { puts("S(&)"); }
    S(S&&) { puts("S(&&)"); }
    ~S() { puts("~S()"); }
};

int main(int argc, char *[]) {
    const size_t reserved {5};
    std::vector<S> v;
    v.reserve(reserved);
    for (size_t i = 0; i < reserved; i++)
        v.emplace_back();
    if (argc > 1)
        v.emplace_back();
    return 0;
}
