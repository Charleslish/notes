#include <iostream>

#include "solution.hpp"

int main() {
  constexpr int kFirstScore = 96;
  constexpr int kSecondScore = 83;
  
  double average = AverageOfTwo(kFirstScore, kSecondScore);

  std::cout << "average: " << average << std::endl;
  std::cout << "whole number part: " << WholeNumberPart(average) << std::endl;

  return 0;
}
