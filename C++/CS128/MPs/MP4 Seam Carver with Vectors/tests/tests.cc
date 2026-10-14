#include <catch2/catch_test_macros.hpp>

#include "image.hpp"
#include "seam_carver.hpp"

TEST_CASE("Default images and carvers are empty", "[empty]") {
  const Image kImage;
  const SeamCarver kCarver;
  REQUIRE(kImage.GetHeight() == 0);
  REQUIRE(kImage.GetWidth() == 0);
  REQUIRE(kCarver.GetVerticalSeam().empty());
  REQUIRE(kCarver.GetHorizontalSeam().empty());
}
