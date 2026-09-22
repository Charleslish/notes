#include "solution.hpp"

// TODO: Define the float-sensor PercentFull: level_liters of
// capacity_liters as a whole percent, fraction discarded. Multiply before
// dividing, and name the percent scale as a constant.
int PercentFull(int level_liters, int capacity_liters) {
  const int kPercentScale = 100;
  return level_liters * kPercentScale / capacity_liters;
}
// TODO: Define the pressure-sensor PercentFull: level_meters of
// tank_depth_meters as a whole percent, truncated toward zero with
// static_cast<int>.
int PercentFull(double level_meters, double tank_depth_meters) {
  const int kPercentScale = 100;
  return static_cast<int>(level_meters * kPercentScale / tank_depth_meters);
}
// TODO: Define MinutesUntilEmpty: whole minutes of draining at rate liters
// per minute until the tank is empty; a partly used minute counts, and an
// already empty tank needs 0.
int MinutesUntilEmpty(int level, int rate) {
  return (level + rate - 1) / rate;
}