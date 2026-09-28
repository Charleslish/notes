#include <iostream>
#include <string>

#include "solution.hpp"

int main() {
  std::string typed("9999");
  if (IsValidDisplay(typed)) {
    std::cout << typed << " is a valid display" << std::endl;
  } else {
    std::cout << typed << " is not a valid display" << std::endl;
  }
  std::cout << "after one click: " << Advance(typed) << std::endl;
  std::cout << "clicks from 0280 to 0284: " << ClicksBetween("0280", "0284") << std::endl;
  return 0;
}
