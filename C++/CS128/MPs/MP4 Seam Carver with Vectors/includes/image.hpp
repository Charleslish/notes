#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>

#include "pixel.hpp"

class Image {
 public:
  Image() = default;
  explicit Image(const std::vector<std::vector<Pixel>>& pixels);
  unsigned int GetHeight() const;
  unsigned int GetWidth() const;
  Pixel GetPixel(unsigned int row, unsigned int col) const;
  void SetPixel(unsigned int row, unsigned int col, const Pixel& pixel);
  void Crop(unsigned int new_height, unsigned int new_width);

 private:
  std::vector<std::vector<Pixel>> pixels_;
};

#endif
