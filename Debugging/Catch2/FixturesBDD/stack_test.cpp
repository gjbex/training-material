#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <stack>

int fac(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

SCENARIO( "stack test", "[stack]" ) {
    GIVEN( "stack with numbers 1 to 5" ) {
        const int max_val {5};
        std::stack<int> data;
        for (int i = 1; i <= max_val; ++i)
            data.push(i);
        WHEN( "computing sum" ) {
            int sum {0};
            while (!data.empty()) {
                sum += data.top();
                data.pop();
            }
            THEN( "sum == 5*6/2" ) {
                REQUIRE( sum == max_val*(max_val + 1)/2 );
            }
        }
        WHEN( "computing product" ) {
            int prod {1};
            while (!data.empty()) {
                prod *= data.top();
                data.pop();
            }
            THEN( "product == 5!" ) {
                REQUIRE( prod == fac(max_val) );
            }
        }
    }
}
