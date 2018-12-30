#include <catch2/catch.hpp>
#include <stdexcept>

#include "fac.h"

SCENARIO( "factorial function return values and exceptions", "[fac]" ) {
    GIVEN( "factorial function 'fac'" ) {
        WHEN( "argument == 0" ) {
            THEN( "fac(0) == 1" ) {
                REQUIRE( fac(0) == 1 );
            }
        }
        WHEN( "argument > 0" ) {
            THEN( "fac(n) == n*fac(n-1)" ) {
                for (int i = 1; i < 6; i++)
                    REQUIRE( fac(i) == i*fac(i - 1) );
            }
        }
        WHEN( "argument < 0" ) {
            THEN( "exception thrown" ) {
                REQUIRE_THROWS_AS( fac(-1), std::domain_error );
            }
        }
    }
}
