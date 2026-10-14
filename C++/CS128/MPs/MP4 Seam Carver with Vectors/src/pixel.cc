#include "pixel.hpp"

#include <cassert>

Pixel::Pixel(int red, int green, int blue) : red_(red), green_(green), blue_(blue) {}

int Pixel::GetRed() const { return red_; }

int Pixel::GetGreen() const { return green_; }

int Pixel::GetBlue() const { return blue_; }

bool operator==(const Pixel& lhs, const Pixel& rhs) {
  return lhs.GetRed() == rhs.GetRed() && lhs.GetGreen() == rhs.GetGreen() && lhs.GetBlue() == rhs.GetBlue();
}
