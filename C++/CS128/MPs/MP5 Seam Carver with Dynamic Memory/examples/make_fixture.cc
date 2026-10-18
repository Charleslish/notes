#include <iostream>

#include "image.hpp"
#include "pixel.hpp"
#include "png_io.hpp"

int main() {
  constexpr unsigned int kSize = 3;
  const Pixel kPixels[kSize][kSize] = {
      {Pixel(0, 0, 0), Pixel(1, 1, 1), Pixel(0, 0, 0)},
      {Pixel(1, 1, 0), Pixel(0, 1, 0), Pixel(0, 0, 1)},
      {Pixel(1, 1, 1), Pixel(1, 0, 1), Pixel(1, 1, 1)}};
  Image image(kSize, kSize);
  for (unsigned int row = 0; row < kSize; ++row) {
    for (unsigned int col = 0; col < kSize; ++col) {
      image.SetPixel(row, col, kPixels[row][col]);
    }
  }
  if (!WritePng("examples/my-energy.png", image)) {
    std::cerr << "Could not write examples/my-energy.png\n";
    return 1;
  }
  return 0;
}
