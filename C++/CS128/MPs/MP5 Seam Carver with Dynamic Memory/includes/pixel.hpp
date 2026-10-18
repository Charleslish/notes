#ifndef PIXEL_HPP
#define PIXEL_HPP

class Pixel {
 public:
  Pixel() = default;
  Pixel(int red, int green, int blue);
  int GetRed() const;
  int GetGreen() const;
  int GetBlue() const;

 private:
  int red_ = 0;
  int green_ = 0;
  int blue_ = 0;
};

bool operator==(const Pixel& lhs, const Pixel& rhs);

#endif
