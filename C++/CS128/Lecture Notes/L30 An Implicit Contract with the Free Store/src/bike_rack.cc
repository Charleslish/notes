#include "bike_rack.hpp"

BikeRack::BikeRack(unsigned int size) : size_(size) {
  bikes_ = new int[size_]{};
}

BikeRack::~BikeRack() {
  delete[] bikes_;
}

unsigned int BikeRack::Size() const {
  return size_;
}

bool BikeRack::Park(unsigned int slot, int bike) {
  if (slot >= size_ || bikes_[slot] != 0) 
    return false;
  bikes_[slot] = bike;
  return true;
}

bool BikeRack::BikeAt(unsigned int slot, int& bike) const {
  if (slot >= size_ || bikes_[slot] == 0) 
    return false;
  bike = bikes_[slot];
  return true;
}

bool BikeRack::Resize(unsigned int size) {
  if (size == 0)
    return false;
  int* new_bikes = new int[size]{};
  unsigned int copy_size = (size < size_) ? size : size_;
  for (unsigned int i = 0; i < copy_size; ++i)
    new_bikes[i] = bikes_[i];
  delete[] bikes_;
  bikes_ = new_bikes;
  size_ = size;
  return true;
}

void BikeRack::TakeFrom(BikeRack& other) {
  if (this == &other)
    return;
  delete[] bikes_;
  bikes_ = other.bikes_;
  size_ = other.size_;
  other.bikes_ = nullptr;
  other.size_ = 0;
}