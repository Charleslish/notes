#include "utilities.hpp"

bool Coord::operator==(const Coord& other) const {
  return row == other.row && col == other.col;
}

bool Coord::operator<(const Coord& other) const {
  return row < other.row || (row == other.row && col < other.col);
}
