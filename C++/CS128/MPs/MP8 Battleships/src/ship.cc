#include "ship.hpp"

Ship::Ship(const Ship& other) {
  for (Segment* current = other.head_; current != nullptr; current = current->next)
    Append(current->row, current->col, current->original_index);
}

Ship& Ship::operator=(const Ship& other) {
  if (this == &other)
    return *this;
  Clear();
  for (Segment* current = other.head_; current != nullptr; current = current->next)
    Append(current->row, current->col, current->original_index);
  return *this;
}

Ship::~Ship() {
  Clear();
}

Segment* Ship::Append(unsigned int row, unsigned int col,
                      unsigned int original_index) {
  Segment* added = new Segment{row, col, original_index, tail_, nullptr};
  if (tail_ != nullptr)
    tail_->next = added;
  else
    head_ = added;
  tail_ = added;
  ++length_;
  return added;
}

void Ship::Remove(Segment* segment) {
  if (segment->prev != nullptr)
    segment->prev->next = segment->next;
  else
    head_ = segment->next;
  if (segment->next != nullptr)
    segment->next->prev = segment->prev;
  else
    tail_ = segment->prev;
  delete segment;
  --length_;
}

Segment* Ship::Center() const {
  if (head_ == nullptr)
    return nullptr;
  Segment* current = head_;
  for (unsigned int i = 0; i < (length_ - 1) / 2; ++i)
    current = current->next;
  return current;
}

void Ship::Clear() {
  Segment* current = head_;
  while (current != nullptr) {
    Segment* next = current->next;
    delete current;
    current = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;
}

Segment* Ship::InsertInOrder(unsigned int row, unsigned int col,
                             unsigned int original_index) {
  Segment* current = head_;
  while (current != nullptr && current->original_index < original_index)
    current = current->next;
  if (current == nullptr)
    return Append(row, col, original_index);
  Segment* added = new Segment{row, col, original_index, current->prev, current};
  if (current->prev != nullptr)
    current->prev->next = added;
  else
    head_ = added;
  current->prev = added;
  ++length_;
  return added;
}

Segment* Ship::Bow() const {
  return head_;
}

Segment* Ship::Stern() const {
  return tail_;
}

bool Ship::IsSunk() const {
  return head_ == nullptr;
}

unsigned int Ship::Length() const {
  return length_;
}
