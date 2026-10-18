#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "pixel.hpp"

class Image {
 public:
  Image() = default;
  Image(const Image& other);
  Image& operator=(const Image& other);
  ~Image();
  Image(unsigned int height, unsigned int width);
  unsigned int GetHeight() const;
  unsigned int GetWidth() const;
  Pixel GetPixel(unsigned int row, unsigned int col) const;
  void SetPixel(unsigned int row, unsigned int col, const Pixel& pixel);
  void Crop(unsigned int new_height, unsigned int new_width);

 private:
  Pixel** pixels_ = nullptr;
  unsigned int height_ = 0;
  unsigned int width_ = 0;
};

#endif
