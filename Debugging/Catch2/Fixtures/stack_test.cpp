#define  CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <stack>

class VectorFixture {
    protected:
        std::stack<int> data;
        const int max_value {5};
    public:
        VectorFixture() : data() {
            for (int i = 1; i <= max_value; ++i)
                data.push(i);
        };
};

TEST_CASE_METHOD(VectorFixture, "sum", "[stack]") {
    int sum {0};
    while (!data.empty()) {
        sum += data.top();
        data.pop();
    }
    REQUIRE( sum == max_value*(max_value + 1)/2 );
}

int fac(int n) {
    if (n < 2)
        return 1;
    else
        return n*fac(n - 1);
}

TEST_CASE_METHOD(VectorFixture, "product", "[stack]") {
    int prod {1};
    while (!data.empty()) {
        prod *= data.top();
        data.pop();
    }
    REQUIRE( prod == fac(max_value) );
}
