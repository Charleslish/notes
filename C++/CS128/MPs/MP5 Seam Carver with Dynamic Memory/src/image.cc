#include "image.hpp"

Image::Image(unsigned int height, unsigned int width): height_(height), width_(width) {
  if (height_ == 0) 
    return;
  pixels_ = new Pixel*[height_];
  for (unsigned int row = 0; row < height_; ++row) 
    pixels_[row] = new Pixel[width_];
}

Image::Image(const Image& other): height_(other.height_), width_(other.width_) {
  if (height_ == 0)
    return;
  pixels_ = new Pixel*[height_];
  for (unsigned int row = 0; row < height_; ++row) {
    pixels_[row] = new Pixel[width_];
    for (unsigned int col = 0; col < width_; ++col)
      pixels_[row][col] = other.pixels_[row][col];
  }
}

Image& Image::operator=(const Image& other) {
  if (this == &other)
    return *this;
  for (unsigned int row = 0; row < height_; ++row)
    delete[] pixels_[row];
  delete[] pixels_;
  pixels_ = nullptr;
  height_ = 0;
  width_ = 0;
  if (other.height_ == 0)
    return *this;
  height_ = other.height_;
  width_ = other.width_;
  pixels_ = new Pixel*[height_];
  for (unsigned int row = 0; row < height_; ++row) {
    pixels_[row] = new Pixel[width_];
    for (unsigned int col = 0; col < width_; ++col) 
      pixels_[row][col] = other.pixels_[row][col];
  }
  return *this;
}

Image::~Image() {
  for (unsigned int row = 0; row < height_; ++row)
    delete[] pixels_[row];
  delete[] pixels_;
}

unsigned int Image::GetHeight() const { return height_; }
unsigned int Image::GetWidth() const { return width_; }

Pixel Image::GetPixel(unsigned int row, unsigned int col) const { return pixels_[row][col]; }

void Image::SetPixel(unsigned int row, unsigned int col, const Pixel& pixel) { pixels_[row][col] = pixel; }

void Image::Crop(unsigned int new_height, unsigned int new_width) {
  if (new_height == 0) {
    for (unsigned int row = 0; row < height_; ++row)
      delete[] pixels_[row];
    delete[] pixels_;
    pixels_ = nullptr;
    height_ = 0;
    width_ = 0;
    return;
  }
  for (unsigned int row = new_height; row < height_; ++row)
    delete[] pixels_[row];
  height_ = new_height;
  width_ = new_width;
}