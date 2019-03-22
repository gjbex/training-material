#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

#include "sort.h"

SCENARIO( "sorting", "[sorting]" ) {
    GIVEN( "vector of 5 int, all 1 or 0" ) {
        std::vector<int> data {1, 0, 0, 1, 0};
        std::vector<int> sorted_data {0, 0, 0, 1, 1};
        WHEN( "naive sort" ) {
            naive_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
        WHEN( "quick sort" ) {
            quick_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
    }
    GIVEN( "vector of 2 int, sorted" ) {
        std::vector<int> data {0, 1};
        std::vector<int> sorted_data {0, 1};
        WHEN( "naive sort" ) {
            naive_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
        WHEN( "quick sort" ) {
            quick_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
    }
    GIVEN( "vector of 2 int, unsorted" ) {
        std::vector<int> data {1, 0};
        std::vector<int> sorted_data {0, 1};
        WHEN( "naive sort" ) {
            naive_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
        WHEN( "quick sort" ) {
            quick_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
    }
    GIVEN( "vector of 6 double" ) {
        std::vector<double> data {3.2, 0.7, -1, 2.3, 5.7, 1.2};
        std::vector<double> sorted_data {-1, 0.7, 1.2, 2.3, 3.2, 5.7};
        WHEN( "naive sort" ) {
            naive_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
        WHEN( "quick sort" ) {
            quick_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
    }
    GIVEN( "empty vector of strings" ) {
        std::vector<std::string> data {};
        std::vector<std::string> sorted_data {};
        WHEN( "naive sort" ) {
            naive_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
        WHEN( "quick sort" ) {
            quick_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
    }
    GIVEN( "vector of 1 string" ) {
        std::vector<std::string> data {"hello"};
        std::vector<std::string> sorted_data {"hello"};
        WHEN( "naive sort" ) {
            naive_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
        WHEN( "quick sort" ) {
            quick_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
    }
    GIVEN( "vector of 2 strings, sorted" ) {
        std::vector<std::string> data {"hello", "world"};
        std::vector<std::string> sorted_data {"hello", "world"};
        WHEN( "naive sort" ) {
            naive_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
        WHEN( "quick sort" ) {
            quick_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
    }
    GIVEN( "vector of 3 strings, inverse sorted" ) {
        std::vector<std::string> data {"world", "hello", "gjb"};
        std::vector<std::string> sorted_data {"gjb", "hello", "world"};
        WHEN( "naive sort" ) {
            naive_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
        WHEN( "quick sort" ) {
            quick_sort(data);
            THEN( "data is sorted" ) {
                REQUIRE( data == sorted_data );
            }
        }
    }
}
