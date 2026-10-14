#include <iostream>
#include <vector>

#include "image.hpp"
#include "pixel.hpp"
#include "png_io.hpp"

int main() {
  const std::vector<std::vector<Pixel>> kPixels{
      {Pixel(0, 0, 0), Pixel(1, 1, 1), Pixel(0, 0, 0)},
      {Pixel(1, 1, 0), Pixel(0, 1, 0), Pixel(0, 0, 1)},
      {Pixel(1, 1, 1), Pixel(1, 0, 1), Pixel(1, 1, 1)}};
  const Image kImage(kPixels);
  if (!WritePng("examples/my-energy.png", kImage)) {
    std::cerr << "Could not write examples/my-energy.png\n";
    return 1;
  }
  return 0;
}
