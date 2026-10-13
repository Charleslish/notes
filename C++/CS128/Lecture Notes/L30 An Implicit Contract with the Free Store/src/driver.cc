#include <iostream>

#include "bike_rack.hpp"

int main() {
  constexpr unsigned int kSlots = 4;
  constexpr unsigned int kMoreSlots = 6;
  constexpr unsigned int kSlot = 1;
  constexpr int kBike = 3070;

  BikeRack north(kSlots);
  const bool kParked = north.Park(kSlot, kBike);
  std::cout << "park " << kBike << " in slot " << kSlot << ": " << kParked
            << std::endl;

  int bike = 0;
  const bool kFound = north.BikeAt(kSlot, bike);
  std::cout << "bike at slot " << kSlot << ": " << kFound << ", bike " << bike
            << std::endl;

  const bool kResized = north.Resize(kMoreSlots);
  std::cout << "resize to " << kMoreSlots << ": " << kResized << ", size "
            << north.Size() << std::endl;

  BikeRack south(kSlots);
  south.TakeFrom(north);
  std::cout << "south size " << south.Size() << ", north size "
            << north.Size() << std::endl;
  return 0;
}
