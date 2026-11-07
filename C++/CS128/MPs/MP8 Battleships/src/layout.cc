#include "layout.hpp"

#include <cstddef>

#include "board.hpp"
#include "ship.hpp"

unsigned int BoardLayoutSignature() {
  const unsigned int parts[] = {
      sizeof(Coord),     alignof(Coord),     sizeof(Segment),
      alignof(Segment),  sizeof(Cell),       alignof(Cell),
      sizeof(Ship),      alignof(Ship),      sizeof(Board),
      alignof(Board),    sizeof(ShotReport), alignof(ShotReport),
      offsetof(Segment, original_index),     offsetof(Segment, prev),
      offsetof(Segment, next),               offsetof(Cell, state),
      offsetof(Cell, original_index),        offsetof(Cell, segment),
      offsetof(Coord, col)};
  unsigned int signature = 17;
  for (unsigned int part : parts) {
    signature = signature * 31 + part;
  }
  return signature;
}
