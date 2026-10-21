#include "pixel.hpp"

Pixel::Pixel(int r, int g, int b) : r_(r), g_(g), b_(b) {}

int Pixel::GetR() const { return r_; }

int Pixel::GetG() const { return g_; }

int Pixel::GetB() const { return b_; }

std::ostream& operator<<(std::ostream& os, const Pixel& p) {
  os << "(" << p.r_ << ", " << p.g_ << ", " << p.b_ << ")";
  return os;
}

bool Pixel::operator>(const Pixel& other) const {
    return (r_ + g_ + b_) > (other.r_ + other.g_ + other.b_);
}