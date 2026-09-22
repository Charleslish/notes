#include "solution.hpp"

int TotalPoints(int base, int bonus_count, int bonus_value) {
  // TODO: Return the base points plus the points earned from the bonuses.
  return base + bonus_count * bonus_value;
  return 0;
}

int RemainingPoints(int total, int first_penalty, int second_penalty) {
  // TODO: Return what remains of total after both penalties are taken off it.
  return total - first_penalty - second_penalty;
  return 0;
}

bool IsEligible(bool is_open, int points, int threshold) {
  // TODO: Return whether the term is open and points has reached threshold.
  return is_open && points >= threshold;
  return false;
}
