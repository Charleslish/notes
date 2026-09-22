#include "solution.hpp"

double AverageOfTwo(int first, int second) {
  // TODO: Return the average of first and second, keeping any half.
  const double kHalf = 0.5;
  return (first + second) * kHalf;
  return 0.0;
}

int WholeNumberPart(double value) {
  // TODO: Return the whole-number part of value.
  return static_cast<int>(value);
  return 0;
}
