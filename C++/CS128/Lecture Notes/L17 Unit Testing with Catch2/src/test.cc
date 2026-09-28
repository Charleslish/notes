#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "tank.hpp"

TEST_CASE("an empty tank is low", "[student]") {
    const double kCurrent = 0.0;
    REQUIRE(TankLevel(kCurrent) == "low");
}
TEST_CASE("a tank is usable", "[student]") {
    const double kCurrent1 = 50.0;
    const double kCurrent2 = 200.0;
    const double kCurrent3 = 499.999999;
    REQUIRE(TankLevel(kCurrent1) == "usable");
    REQUIRE(TankLevel(kCurrent2) == "usable");
    REQUIRE(TankLevel(kCurrent3) == "usable");
}
TEST_CASE("a tank is full", "[student]") {
    const double kCurrent = 500.0;
    REQUIRE(TankLevel(kCurrent) == "full");
}
TEST_CASE("a tank is overflowing", "[student]") {
    const double kCurrent = 600.0;
    REQUIRE(TankLevel(kCurrent) == "overflowing");
}
TEST_CASE("a tank has to hold a positive number of litres", "[student]") {
    const double kCurrent = -5.0;
    REQUIRE(TankLevel(kCurrent) == "?");
}