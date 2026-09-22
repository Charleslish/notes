#include "solution.hpp"

int MinutesToFill(int level, int capacity, int rate) {
  // TODO: Return the whole minutes of pumping until the tank holds at least
  // capacity liters. A partly used minute counts; already full needs 0.
  if (level >= capacity) {
    return 0;
  }
  return (capacity - level + rate - 1) / rate;
}

int GrowthOn(int day, int first, int second) {
  // TODO: Rotate two objects through the days with a loop: each new day's
  // count is the sum of the previous two days' counts.
  const int kSecond = 2;
  if (day == 0) {
    return first;
  }
  if (day == 1) {
    return second;
  }
  int current = 0;
  for (int i = kSecond; i <= day; i++) {
    current = first + second;
    first = second;
    second = current;
  }
  return current;
}

bool ReadingsAgree(int first_reading, int second_reading, int tolerance) {
  // TODO: Return whether the readings differ by at most tolerance, in
  // either direction, as one compound condition.
  return (first_reading <= second_reading + tolerance) && (first_reading >= second_reading - tolerance);
}
