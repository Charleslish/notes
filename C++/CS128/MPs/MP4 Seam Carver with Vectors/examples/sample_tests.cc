#include "image.hpp"
#include "seam_carver.hpp"

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "pixel.hpp"
#include "png_io.hpp"

TEST_CASE("Setting a pixel changes only its color", "[image-set]") {
  const Pixel kBlack(0, 0, 0);
  const Pixel kRed(255, 0, 0);
  const std::vector<std::vector<Pixel>> kPixels(2, std::vector<Pixel>(3, kBlack));
  Image image(kPixels);

  image.SetPixel(1, 2, kRed);
  REQUIRE(image.GetHeight() == 2);
  REQUIRE(image.GetWidth() == 3);
  for (unsigned int row = 0; row < 2; ++row) {
    for (unsigned int col = 0; col < 3; ++col) {
      const Pixel kExpected = (row == 1 && col == 2) ? kRed : kBlack;
      REQUIRE(image.GetPixel(row, col) == kExpected);
    }
  }
}

TEST_CASE("Cropping retains the top-left rectangle", "[image-crop]") {
  const Pixel kRed(255, 0, 0);
  const Pixel kGreen(0, 255, 0);
  const Pixel kBlue(0, 0, 255);
  const std::vector<std::vector<Pixel>> kPixels{
      {kRed, kGreen, kBlue}, {kBlue, kRed, kGreen}, {kGreen, kBlue, kRed}};
  Image image(kPixels);
  const std::vector<std::vector<Pixel>> kExpected{{kRed}, {kBlue}};

  image.Crop(2, 1);
  REQUIRE(image.GetHeight() == 2);
  REQUIRE(image.GetWidth() == 1);
  for (unsigned int row = 0; row < kExpected.size(); ++row) {
    for (unsigned int col = 0; col < kExpected[row].size(); ++col) {
      REQUIRE(image.GetPixel(row, col) == kExpected[row][col]);
    }
  }
}

TEST_CASE("Energy includes wrapping at every border", "[energy]") {
  Image image;
  REQUIRE(ReadPng("examples/energy-3x3.png", &image));
  const SeamCarver kCarver(image);
  const std::vector<std::vector<int>> kExpected{
      {4, 3, 5}, {5, 4, 4}, {3, 2, 2}};

  REQUIRE(kCarver.GetHeight() == 3);
  REQUIRE(kCarver.GetWidth() == 3);
  for (unsigned int row = 0; row < kExpected.size(); ++row) {
    for (unsigned int col = 0; col < kExpected[row].size(); ++col) {
      REQUIRE(kCarver.GetEnergy(row, col) == kExpected[row][col]);
    }
  }
}

TEST_CASE("A uniform image selects the leftmost straight seam", "[vertical-ties]") {
  const std::vector<std::vector<Pixel>> kPixels(
      3, std::vector<Pixel>(4, Pixel(80, 120, 160)));
  const Image kImage(kPixels);
  const SeamCarver kCarver(kImage);
  const std::vector<unsigned int> kExpected{0, 0, 0};

  REQUIRE(kCarver.GetVerticalSeam() == kExpected);
  REQUIRE(kCarver.GetWidth() == 4);
  REQUIRE(kCarver.GetHeight() == 3);
}

TEST_CASE("Horizontal carving preserves pixels across a bent seam", "[horizontal-removal]") {
  Image image;
  REQUIRE(ReadPng("examples/bent-seams-4x3.png", &image));
  SeamCarver carver(image);
  const std::vector<unsigned int> kSeam{0, 1, 0, 1};
  const std::vector<std::vector<Pixel>> kExpected{
      {Pixel(6, 6, 6), Pixel(2, 2, 2), Pixel(3, 3, 3), Pixel(4, 4, 4)},
      {Pixel(5, 5, 5), Pixel(9, 9, 9), Pixel(2, 2, 2), Pixel(0, 0, 0)}};

  REQUIRE(carver.GetHorizontalSeam() == kSeam);
  REQUIRE(carver.RemoveHorizontalSeam());
  REQUIRE(carver.GetHeight() == 2);
  REQUIRE(carver.GetWidth() == 4);
  for (unsigned int row = 0; row < kExpected.size(); ++row) {
    for (unsigned int col = 0; col < kExpected[row].size(); ++col) {
      REQUIRE(carver.GetImage().GetPixel(row, col) == kExpected[row][col]);
    }
  }
}
