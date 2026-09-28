#include <catch2/catch_test_macros.hpp>

#include "tiles.hpp"

TEST_CASE("a row divides exactly", "[across]") {
  REQUIRE(TilesAcross(3600, 300) == 12);
}

TEST_CASE("a row that does not divide exactly leaves the remainder", "[across]") {
  REQUIRE(TilesAcross(3650, 300) == 12);
}

TEST_CASE("a tile of no width covers nothing", "[across]") {
  REQUIRE(TilesAcross(3600, 0) == 0);
}

TEST_CASE("a floor is the rows times the columns", "[floor]") {
  REQUIRE(TilesForFloor(3600, 2400, 300) == 96);
}
