#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

// Returns the elements of values rotated no_rotations positions to the left.
// Rotating an empty vector produces an empty vector. A rotation count at or
// above the size wraps: rotating by exactly the size, or any multiple of it,
// returns the elements unchanged.
// RotateLeft({1, 2, 3}, 1) returns {2, 3, 1}.
// RotateLeft({2, 4, 6, 8}, 5) returns {4, 6, 8, 2}.
std::vector<int> RotateLeft(const std::vector<int>& values, unsigned int no_rotations);

#endif  // closes the include guard
