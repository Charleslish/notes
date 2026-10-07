#include <iostream>

#include "solution.hpp"

int main() {
  constexpr unsigned int kPointCount = 7;
  const int kSurvey[kPointCount] = {120, 135, 135, 110, 140, 165, 150};

  std::cout << "Summits: " << CountSummits(kSurvey, kPointCount) << std::endl;

  const Climb kLongest = LongestClimb(kSurvey, kPointCount);
  std::cout << "Longest climb: starts at index " << kLongest.start << ", "
            << kLongest.length << " points" << std::endl;

  const int* const kEnd = kSurvey + kPointCount;
  const int* const kHighest = HighestPoint(kSurvey, kEnd);
  if (kHighest != kEnd) {
    std::cout << "Highest point: " << *kHighest << std::endl;
  }

  int elevations[kPointCount] = {};
  for (unsigned int i = 0; i < kPointCount; ++i) {
    elevations[i] = kSurvey[i];
  }
  SmoothInPlace(elevations, kPointCount);
  std::cout << "Smoothed:";
  for (const int& elevation : elevations) {
    std::cout << " " << elevation;
  }
  std::cout << std::endl;
  return 0;
}
