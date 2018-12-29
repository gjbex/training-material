#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <functional>
#include <random>

using Distribution = std::function<int ()>;

std::string generate_ip4_address(Distribution distr) {
    std::string ip4_address {std::to_string(distr())};
    for (int i = 0; i < 3; ++i)
        ip4_address += "." + std::to_string(distr());
    return ip4_address;
}

using Catch::Matchers::Matches;

TEST_CASE("random IP4 address generation") {
    std::mt19937::result_type seed {1234};
    auto distr = std::bind(std::uniform_int_distribution<int>(0, 255),
                           std::mt19937(seed));
    for (int i = 0; i < 10; ++i)
        REQUIRE_THAT( generate_ip4_address(distr),
                      Matches(R"(^\d{1,3}(?:\.\d{1,3}){3}$)") );
}
