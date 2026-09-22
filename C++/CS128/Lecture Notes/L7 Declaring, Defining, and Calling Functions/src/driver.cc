#include <iostream>

#include "solution.hpp"

int main() {
  constexpr int kLevel = 5;
  constexpr int kCapacity = 12;
  constexpr int kRate = 4;
  constexpr int kDay = 6;
  constexpr int kFirstSeed = 3;
  constexpr int kSecondSeed = 3;
  constexpr int kFirstReading = 10;
  constexpr int kSecondReading = 13;
  constexpr int kTolerance = 3;

  std::cout << "minutes to fill: "
            << MinutesToFill(kLevel, kCapacity, kRate) << std::endl;
  std::cout << "leaves on day " << kDay << ": "
            << GrowthOn(kDay, kFirstSeed, kSecondSeed) << std::endl;
  std::cout << "sensors agree: "
            << ReadingsAgree(kFirstReading, kSecondReading, kTolerance)
            << std::endl;

  return 0;
}
