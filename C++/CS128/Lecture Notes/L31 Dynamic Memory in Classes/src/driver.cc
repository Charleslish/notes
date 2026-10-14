#include <iostream>

#include "manifest.hpp"

int main() {
  constexpr unsigned int kLanes = 4;
  constexpr unsigned int kFewerLanes = 2;
  constexpr unsigned int kSlot = 1;
  constexpr int kVehicle = 4417;
  constexpr int kOtherVehicle = 2093;

  Manifest morning(kLanes);
  const bool kLoaded = morning.Load(kSlot, kVehicle);
  std::cout << "load " << kVehicle << " in slot " << kSlot << ": " << kLoaded
            << std::endl;

  Manifest copy(morning);
  copy.Load(0, kOtherVehicle);
  int vehicle = 0;
  const bool kInMorning = morning.VehicleAt(0, vehicle);
  std::cout << "copy size " << copy.Size() << ", vehicle in morning slot 0: "
            << kInMorning << std::endl;

  Manifest evening(kFewerLanes);
  evening = morning;
  const bool kFound = evening.VehicleAt(kSlot, vehicle);
  std::cout << "evening size " << evening.Size() << ", vehicle at slot "
            << kSlot << ": " << kFound << ", vehicle " << vehicle << std::endl;
  return 0;
}
