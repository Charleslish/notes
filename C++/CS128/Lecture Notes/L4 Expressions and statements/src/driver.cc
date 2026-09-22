#include <iostream>

#include "solution.hpp"

int main() {
  constexpr int kBase = 240;
  constexpr int kBonusCount = 2;
  constexpr int kBonusValue = 15;
  constexpr int kFirstPenalty = 15;
  constexpr int kSecondPenalty = 3;
  constexpr int kHonorsThreshold = 250;

  int total = TotalPoints(kBase, kBonusCount, kBonusValue);
  int remaining = RemainingPoints(total, kFirstPenalty, kSecondPenalty);

  std::cout << "total: " << total << std::endl;
  std::cout << "remaining: " << remaining << std::endl;
  std::cout << "eligible: " << IsEligible(true, remaining, kHonorsThreshold)
            << std::endl;

  return 0;
}
