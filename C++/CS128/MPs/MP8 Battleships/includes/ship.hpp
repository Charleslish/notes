#ifndef SHIP_HPP
#define SHIP_HPP

#include "segment.hpp"

class Ship {
 public:
  Ship() = default;
  Ship(const Ship& other);
  Ship& operator=(const Ship& other);
  ~Ship();

  Segment* Append(unsigned int row, unsigned int col, unsigned int original_index);
  void Remove(Segment* segment);
  Segment* Center() const;
  void Clear();
  Segment* InsertInOrder(unsigned int row,
                         unsigned int col,
                         unsigned int original_index);

  Segment* Bow() const;
  Segment* Stern() const;
  bool IsSunk() const;
  unsigned int Length() const;

 private:
  Segment* head_ = nullptr;
  Segment* tail_ = nullptr;
  unsigned int length_ = 0;
};

#endif
