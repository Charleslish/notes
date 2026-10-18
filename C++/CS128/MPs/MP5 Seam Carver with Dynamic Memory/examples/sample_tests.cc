#include "image.hpp"
#include "seam_carver.hpp"

#include <catch2/catch_test_macros.hpp>

#include "pixel.hpp"
#include "png_io.hpp"

TEST_CASE("Setting a pixel changes only its color", "[image-set]") {
  const Pixel kBlack(0, 0, 0);
  const Pixel kRed(255, 0, 0);
  Image image(2, 3);
  for (unsigned int row = 0; row < 2; ++row) {
    for (unsigned int col = 0; col < 3; ++col) {
      image.SetPixel(row, col, kBlack);
    }
  }

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
  const Pixel kPixels[3][3] = {
      {kRed, kGreen, kBlue}, {kBlue, kRed, kGreen}, {kGreen, kBlue, kRed}};
  Image image(3, 3);
  for (unsigned int row = 0; row < 3; ++row) {
    for (unsigned int col = 0; col < 3; ++col) {
      image.SetPixel(row, col, kPixels[row][col]);
    }
  }

  image.Crop(2, 1);
  REQUIRE(image.GetHeight() == 2);
  REQUIRE(image.GetWidth() == 1);
  REQUIRE(image.GetPixel(0, 0) == kRed);
  REQUIRE(image.GetPixel(1, 0) == kBlue);
}

TEST_CASE("Energy includes wrapping at every border", "[energy]") {
  Image image;
  REQUIRE(ReadPng("examples/energy-3x3.png", &image));
  const SeamCarver kCarver(image);
  const int kExpected[3][3] = {{4, 3, 5}, {5, 4, 4}, {3, 2, 2}};

  REQUIRE(kCarver.GetHeight() == 3);
  REQUIRE(kCarver.GetWidth() == 3);
  for (unsigned int row = 0; row < 3; ++row) {
    for (unsigned int col = 0; col < 3; ++col) {
      REQUIRE(kCarver.GetEnergy(row, col) == kExpected[row][col]);
    }
  }
}

TEST_CASE("A uniform image selects the leftmost straight seam", "[vertical-ties]") {
  Image image(3, 4);
  for (unsigned int row = 0; row < 3; ++row) {
    for (unsigned int col = 0; col < 4; ++col) {
      image.SetPixel(row, col, Pixel(80, 120, 160));
    }
  }
  const SeamCarver kCarver(image);

  unsigned int* seam = kCarver.GetVerticalSeam();
  REQUIRE(seam != nullptr);
  for (unsigned int row = 0; row < 3; ++row) {
    REQUIRE(seam[row] == 0);
  }
  delete[] seam;
  REQUIRE(kCarver.GetWidth() == 4);
  REQUIRE(kCarver.GetHeight() == 3);
}

TEST_CASE("Horizontal carving preserves pixels across a bent seam", "[horizontal-removal]") {
  Image image;
  REQUIRE(ReadPng("examples/bent-seams-4x3.png", &image));
  SeamCarver carver(image);
  const unsigned int kSeam[4] = {0, 1, 0, 1};
  const Pixel kExpected[2][4] = {
      {Pixel(6, 6, 6), Pixel(2, 2, 2), Pixel(3, 3, 3), Pixel(4, 4, 4)},
      {Pixel(5, 5, 5), Pixel(9, 9, 9), Pixel(2, 2, 2), Pixel(0, 0, 0)}};

  unsigned int* seam = carver.GetHorizontalSeam();
  REQUIRE(seam != nullptr);
  for (unsigned int col = 0; col < 4; ++col) {
    REQUIRE(seam[col] == kSeam[col]);
  }
  delete[] seam;
  REQUIRE(carver.RemoveHorizontalSeam());
  REQUIRE(carver.GetHeight() == 2);
  REQUIRE(carver.GetWidth() == 4);
  for (unsigned int row = 0; row < 2; ++row) {
    for (unsigned int col = 0; col < 4; ++col) {
      REQUIRE(carver.GetImage().GetPixel(row, col) == kExpected[row][col]);
    }
  }
}

TEST_CASE("Image copies own their pixel rows", "[image-copy-example]") {
  Image original(2, 2);
  original.SetPixel(0, 0, Pixel(10, 20, 30));
  original.SetPixel(0, 1, Pixel(40, 50, 60));
  original.SetPixel(1, 0, Pixel(70, 80, 90));
  original.SetPixel(1, 1, Pixel(100, 110, 120));
  Image copy(original);
  copy.SetPixel(0, 0, Pixel(255, 0, 0));
  REQUIRE(original.GetPixel(0, 0) == Pixel(10, 20, 30));
  Image assigned;
  REQUIRE(&(assigned = original) == &assigned);
  const Image& alias = assigned;
  assigned = alias;
  assigned.Crop(1, 1);
  REQUIRE(assigned.GetPixel(0, 0) == Pixel(10, 20, 30));
  REQUIRE(original.GetHeight() == 2);
}

TEST_CASE("Carvers keep independent images and a stable image reference", "[carver-copy-example]") {
  Image image(2, 2);
  image.SetPixel(0, 0, Pixel(10, 20, 30));
  image.SetPixel(0, 1, Pixel(40, 50, 60));
  image.SetPixel(1, 0, Pixel(70, 80, 90));
  image.SetPixel(1, 1, Pixel(100, 110, 120));
  SeamCarver original(image);
  SeamCarver copy(original);
  REQUIRE(copy.RemoveVerticalSeam());
  REQUIRE(original.GetWidth() == 2);
  REQUIRE(copy.GetWidth() == 1);
  const Image& reference = copy.GetImage();
  copy.SetImage(image);
  REQUIRE(&reference == &copy.GetImage());
  REQUIRE(reference.GetWidth() == 2);
  const SeamCarver& alias = copy;
  REQUIRE(&(copy = alias) == &copy);
  REQUIRE(reference.GetWidth() == 2);
}
