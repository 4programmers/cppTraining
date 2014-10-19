#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "RandomNameGenerator.hpp"
#include <random>

TEST_CASE("RandomNameGenerator works well without arguments", "[RandomNameGenerator]"){
    int seed = 5;
    std::default_random_engine re(5);
    SECTION("A RandomNameGenerator with \"\" in constructor and 0's in when called for generate"){
        RandomNameGenerator<> rng(
            RandomNameGenerator<>::Prefixes{""},
            RandomNameGenerator<>::Cores{""},
            RandomNameGenerator<>::Sufixes{""},
            re
        );
        REQUIRE(rng(0, 0)=="");
    }
}
