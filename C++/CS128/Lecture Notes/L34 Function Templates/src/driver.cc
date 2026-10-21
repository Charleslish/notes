#include <iostream>
#include <string>

#include "larger.hpp"
#include "pixel.hpp"
#include "student.hpp"

int main() {
  // After you implement Larger, these should work:
  std::cout << Larger(10, 20) << std::endl;
  std::cout << Larger(3.14, 2.71) << std::endl;

  Student s1("Alice", 3.8);
  Student s2("Bob", 3.5);
  Student result = Larger(s1, s2);
  std::cout << result.GetName() << std::endl;

  // After you also fix Pixel, this should work:
  Pixel p1(255, 0, 0);
  Pixel p2(0, 255, 0);
  Pixel brighter = Larger(p1, p2);
  std::cout << brighter << std::endl;

  return 0;
}
