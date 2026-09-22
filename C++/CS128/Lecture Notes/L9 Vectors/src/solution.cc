#include "solution.hpp"

std::vector<int> RotateLeft(const std::vector<int>& values, unsigned int no_rotations) {
  // Build the rotated vector with push_back and return it. Handle the empty
  // vector and rotation counts at or above the size before indexing.
  const unsigned int kLength = values.size();
  std::vector<int> rotated(kLength);
  for (unsigned int i = 0; i < kLength; ++i){
    rotated[i] = values[(i + no_rotations % kLength) % kLength];
  }
  return rotated;
}
