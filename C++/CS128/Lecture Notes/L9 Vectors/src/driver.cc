#include <iostream>

#include "solution.hpp"

int main() {
  const unsigned int kRotations = 2;
  std::vector<int> values {1, 2, 3, 4, 5};
  std::vector<int> rotated = RotateLeft(values, kRotations);
  for (unsigned int i = 0; i < rotated.size(); ++i) {
    std::cout << rotated[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
