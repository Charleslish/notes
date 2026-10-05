#include <iostream>
#include <vector>

#include "crane.hpp"

int main() {
  const unsigned int kGantryLimit = 40;
  std::vector<Container> yard = {
      {.code = "MSCU-104", .tonnes = 22, .is_stowed = false},
      {.code = "TGHU-310", .tonnes = 35, .is_stowed = false},
      {.code = "CMAU-221", .tonnes = 48, .is_stowed = false}};

  Crane gantry(kGantryLimit);
  Crane mobile;

  Container* const kHeaviest = gantry.HeaviestLiftable(yard);
  if (kHeaviest != nullptr) {
    std::cout << "heaviest liftable: " << kHeaviest->code << std::endl;
  }
  const bool kLifted = gantry.Lift(kHeaviest);
  std::cout << "lifted: " << kLifted
            << ", holding it: " << gantry.IsHolding(kHeaviest) << std::endl;
  const bool kHanded = gantry.HandOff(&mobile);
  std::cout << "handed to a crane rated " << mobile.GetMaxTonnes()
            << " t: " << kHanded << std::endl;
  const Container* const kOnHook = gantry.Holding();
  if (kOnHook != nullptr) {
    std::cout << "gantry holds: " << kOnHook->code << std::endl;
  }
  const bool kStowed = gantry.Stow();
  std::cout << "stowed: " << kStowed << ", " << yard.at(1).code
            << " is stowed: " << yard.at(1).is_stowed << std::endl;
  const bool kLiftedLight = gantry.Lift(&yard.at(0));
  const bool kHandedLight = gantry.HandOff(&mobile);
  std::cout << "lifted " << yard.at(0).code << ": " << kLiftedLight
            << ", handed off: " << kHandedLight
            << ", mobile holds it: " << mobile.IsHolding(&yard.at(0))
            << std::endl;
  const Container* const kReleased = gantry.Release();
  std::cout << "gantry hook empty: " << (kReleased == nullptr) << std::endl;
  return 0;
}
