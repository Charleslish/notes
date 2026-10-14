#include "image.hpp"

Image::Image(const std::vector<std::vector<Pixel>>& pixels): pixels_(pixels) {}

unsigned int Image::GetHeight() const {
  return static_cast<unsigned int>(pixels_.size());
}

unsigned int Image::GetWidth() const {
  if (pixels_.empty())
    return 0;
  return static_cast<unsigned int>(pixels_[0].size());
}

Pixel Image::GetPixel(unsigned int row, unsigned int col) const {
  return pixels_[row][col];
}

void Image::SetPixel(unsigned int row, unsigned int col, const Pixel& pixel) {
  pixels_[row][col] = pixel;
}

void Image::Crop(unsigned int new_height, unsigned int new_width) {
  for (unsigned int row = 0; row < new_height; ++row)
    pixels_[row].resize(new_width);
  pixels_.resize(new_height);
}
