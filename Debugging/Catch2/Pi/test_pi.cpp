#include <catch2/catch.hpp>
#include <cmath>

#include "pi.h"

TEST_CASE("computing pi as quadrature", "[pi]") {
    REQUIRE( pi(1000) == Approx(3.14).epsilon(1.0e-2) );
    REQUIRE( pi(1000000) == Approx(3.14159).epsilon(1.0e-5) );
    REQUIRE( pi(1000000) == Approx(3.14159265359).epsilon(1.0e-9) );
}
