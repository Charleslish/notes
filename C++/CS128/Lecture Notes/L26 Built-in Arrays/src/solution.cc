#include "solution.hpp"

unsigned int FindPlateauEnd(const int* elevations, unsigned int start, unsigned int size) {
  unsigned int end = start;
  while (end + 1 < size && elevations[end] == elevations[end + 1])
    ++end;
  return end;
}

bool IsSummit(const int* elevations, unsigned int index, unsigned int plateau_end) {
  return elevations[index - 1] < elevations[index] && elevations[plateau_end + 1] < elevations[plateau_end];
}

unsigned int CountSummits(const int* elevations, unsigned int size) {
  if (elevations == nullptr || size < 3) 
    return 0;
  unsigned int count = 0;
  unsigned int index = 1;
  while (index < size - 1) {
    unsigned int plateau_end = FindPlateauEnd(elevations, index, size);
    if (plateau_end < size - 1 && elevations[index - 1] < elevations[index] && elevations[plateau_end + 1] < elevations[plateau_end])
      ++count;
    index = plateau_end + 1;
  }
  return count;
}

Climb LongestClimb(const int* elevations, unsigned int size) {
  Climb longest;
  if (elevations == nullptr || size == 0)
    return longest;
  longest.start = 0;
  longest.length = 1;
  unsigned int start = 0;
  unsigned int length = 1;
  for (unsigned int index = 1; index < size; ++index) {
    if (elevations[index] > elevations[index - 1]) {
      ++length;
      continue;
    } 
    if (length > longest.length) {
      longest.start = start;
      longest.length = length;
    }
    start = index;
    length = 1;
  }
  if (length > longest.length) {
    longest.start = start;
    longest.length = length;
  }
  return longest;
}

void SmoothInPlace(int* elevations, unsigned int size) {
  if (elevations == nullptr || size < 3)
    return;
  int left = elevations[0];
  int current = elevations[1];
  for (unsigned int index = 1; index < size - 1; ++index) {
    int right = elevations[index + 1];
    elevations[index] = (left + current + right) / 3;
    left = current;
    current = right;
  }
}

const int* HighestPoint(const int* first, const int* last) {
  if (first == last) 
    return last;
  const int* highest = first;
  const int* current = first + 1;
  while (current != last) {
    if (*current > *highest)
      highest = current;
    ++current;
  }
  return highest;
}