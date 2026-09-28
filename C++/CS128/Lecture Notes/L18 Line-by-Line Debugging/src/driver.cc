#include <iostream>
#include <vector>

#include "summary.hpp"

int main() {
  const std::vector<double> kReadings = {18.0, 22.0, 25.0, 30.0, 12.0, 40.0};
  const double kThreshold = 20.0;
  const double kLimit = 35.0;
  const Summary kResult = Summarize(kReadings, kThreshold, kLimit);
  std::cout << "longest run: " << kResult.longest_run << std::endl;
  std::cout << "total above: " << kResult.total_above << std::endl;
  std::cout << "steady: " << (kResult.steady ? "yes" : "no") << std::endl;
  return 0;
}
