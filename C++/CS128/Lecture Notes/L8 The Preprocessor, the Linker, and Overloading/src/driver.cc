#include <iostream>

#include "solution.hpp"

int main() {
  constexpr int kLevelLiters = 7;
  constexpr int kCapacityLiters = 8;
  constexpr double kLevelMeters = 1.75;
  constexpr double kTankDepthMeters = 2.0;
  constexpr int kDrainRate = 4;

  std::cout << "float sensor: "
            << PercentFull(kLevelLiters, kCapacityLiters) << "%" << std::endl;
  std::cout << "pressure sensor: "
            << PercentFull(kLevelMeters, kTankDepthMeters) << "%" << std::endl;
  std::cout << "minutes until empty: "
            << MinutesUntilEmpty(kLevelLiters, kDrainRate) << std::endl;

  return 0;
}
