#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <set>

#include "segment.hpp"

struct Coord {
  unsigned int row = 0;
  unsigned int col = 0;
  bool operator==(const Coord& other) const;
  bool operator<(const Coord& other) const;
};

enum class Orientation {
  kHorizontal,
  kVertical,
  kDiagonalDownRight,
  kDiagonalDownLeft
};

enum class CellState { kUnfired, kMiss, kHit };

struct Cell {
  char ship = '.';
  CellState state = CellState::kUnfired;
  unsigned int original_index = 0;
  Segment* segment = nullptr;
};

enum class ShotResult { kMiss, kHit, kSunk, kRepeat };

struct ShotReport {
  ShotResult target = ShotResult::kRepeat;
  std::set<Coord> hits;
  std::set<Coord> misses;
  std::set<char> sunk;
};

#endif
