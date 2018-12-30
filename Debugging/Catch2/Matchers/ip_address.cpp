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
    for (int i = 0; i < 10; ++i) {
        auto ip_address = generate_ip4_address(distr);
        REQUIRE_THAT( ip_address, Matches(R"(^\d{1,3}(?:\.\d{1,3}){3}$)") );
        size_t pos {0};
        size_t old_pos {pos};
        while ((pos = ip_address.find(".", old_pos)) &&
               pos != std::string::npos) {
            auto byte {std::stoi(ip_address.substr(old_pos, pos))};
            REQUIRE( 0 <= byte );
            REQUIRE( byte < 256 );
            old_pos = pos + 1;
        }
    }
}
