#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <iostream>

class Pixel {
 public:
  Pixel(int r, int g, int b);
  int GetR() const;
  int GetG() const;
  int GetB() const;
  friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
  bool operator>(const Pixel& other) const;

 private:
  int r_ = 0;
  int g_ = 0;
  int b_ = 0;
};

#endif